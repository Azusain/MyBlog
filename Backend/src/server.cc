// unix
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <assert.h>
// C++ std
#include <memory>
#include <regex>
#include <sstream>
// std lib <format> in C++ 20
#include <fmt/core.h>
// proj files
#include "http_parser.h"
#include "server.h"
#include "CRequest.h"
#include "utils.h"
#include "logger.h"
#include "service.h"
#include "runtime.h"


Server::Server(uint16_t port)
  :kMaxConnections(10), kBufferSize(1024), kPORT(port) {
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    address_.sin_family = AF_INET;
    address_.sin_addr.s_addr = INADDR_ANY;
    address_.sin_port = htons(kPORT);        
}

void Server::Start() {
  fmt::println("Server runs on {}", kPORT);
  
  // init acceptor
  int addrlen = sizeof(address_);
  int ret = bind(server_fd_, (struct sockaddr *)&(address_), sizeof(address_));
  assert(!ret);
  listen(server_fd_, kMaxConnections);
  epoll_fd_ = epoll_create(1024);

  // init service thread
  pthread_t serv_th;
  pthread_create(&serv_th, nullptr, this->Reader, (void*)this);

  while (true) {
    ssize_t new_socket = accept(server_fd_, (struct sockaddr*)&address_, (socklen_t*)&addrlen);
    fmt::println("accept new connection");
    if(new_socket < 0){
      perror("err accepting socket\n");
      continue;
    }
    // epoll
    epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;  // Edge Trigger
    ev.data.fd = new_socket;
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, new_socket, &ev);
  }
  // @todo: remember rsrc recycling 
  // pthread_join(serv_th, NULL);
}

void* Server::Reader(void* arg) {
  Server* serv_p = (Server*)arg;
  const uint8_t EVENT_BUF_SZ = 10;
  epoll_event evs[EVENT_BUF_SZ];
  
  while (1) {
    int n_events = epoll_wait(serv_p->epoll_fd_, evs, EVENT_BUF_SZ, -1);
    for(size_t i = 0; i < n_events; ++i) {
      if (evs[i].events & EPOLLIN) {
        // parameters
        struct ParserAdaptorStruct pas = {
          evs[i].data.fd, 
          serv_p
        };
        // new thread for each connection
        pthread_t thd;
        pthread_create(&thd, nullptr, Server::ParserAdaptor, (void*)&pas);
        // serv_p -> parser(evs[i].data.fd);
      } else if (evs[i].events & EPOLLHUP) {    
        close(evs[i].data.fd);
      }
    }
  }
  return nullptr;  
}

void Server::Parser(ssize_t fd) {
  // fmt::println("parse msg...");      // @todo: repeated log?

  char buffer[kBufferSize]; 
  memset(buffer, '\0', kBufferSize);
  
  // timeout handler
  // struct timeval timeout;
  // timeout.tv_sec = 3;
  // timeout.tv_usec = 0;
  // socklen_t timeout_len = sizeof(timeout);
  // setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, timeout_len);
  CRequest::HttpParser parser(fd);

  parser.ParseSocketStream();
  auto& request = parser.request_;
  

  // Deal with request and response
  // @todo: request could be cached in a temporary queue 
  CRequest::HttpResponse* hresp_p;
  // Service sv(*req_p);
  std::string addr_v4(CRequest::Utils::getConnAddr(fd));
  
  if(request.method_ == "POST") { // GET routers
    send(fd, "DONE", 4, 0);
  } else if(request.method_ == "OPTIONS") { // CORS
    hresp_p = new CRequest::HttpResponse(200, {
      CRequest::Header_Generator::set_content_len(0),
      CRequest::Header_Generator::set_allow_origin("*"),
      CRequest::Header_Generator::set_allow_methods({"GET", "OPTIONS", "POST"}),
      CRequest::Header_Generator::set_allow_hdrs({"Content-Length", "Content-Type", "Token"})
    });
    Runtime::logger.log(
      {addr_v4, request.method_, "200", "/"}, Runtime::clr_200);
  } else if(request.method_ == "GET") {
    hresp_p = new CRequest::HttpResponse(404, {});
    Runtime::logger.log(
      {addr_v4, request.method_, "404", "/invalid"}, Runtime::clr_404);
  }
  if(hresp_p != nullptr) {
    delete hresp_p;
  }
  shutdown(fd, SHUT_RDWR);
  close(fd); 
  return;
}

void* Server::ParserAdaptor(void* arg) {
  struct ParserAdaptorStruct* p = (ParserAdaptorStruct*)arg; 
  p->serv_p->Parser(p->fd);
  return nullptr;
}
