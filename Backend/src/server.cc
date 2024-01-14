// unix
#include <unistd.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <arpa/inet.h>
// C++ std
#include <memory>
#include <regex>
#include <sstream>
// std lib <format> in C++ 20
#include <fmt/core.h>
// proj files
#include "Server.h"
#include "CRequest.h"
#include "Utils.h"
#include "Logger.h"
#include "Service.h"
#include "Runtime.h"


Server::Server(uint16_t port)
  :MAX_CONNECTIONS(10), BUFFER_SIZE(1024), PORT(port) {
    this -> server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    this -> address_.sin_family = AF_INET;
    this -> address_.sin_addr.s_addr = INADDR_ANY;
    this -> address_.sin_port = htons(this -> PORT);        
}

void Server::start() {
  fmt::println("Server runs on {}", this -> PORT);
  
  // init acceptor
  int addrlen = sizeof(this -> address_);
  bind(server_fd_, (struct sockaddr *)&(this -> address_), sizeof(this -> address_));
  listen(server_fd_, this -> MAX_CONNECTIONS);
  this -> epoll_fd_ = epoll_create(1024);

  // init service thread
  // @todo : need threadpool implementations here~
  pthread_t serv_th;
  pthread_create(&serv_th, nullptr, this -> reader, (void*)this);

  while (true) {
    
    ssize_t new_socket = accept(server_fd_, (struct sockaddr*)&address_, (socklen_t*)&addrlen);
    fmt::println("accept new connection");
    if(new_socket < 0){
      perror("err accepting socket\n");
      continue;
    }
    // epoll
    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = new_socket;
    epoll_ctl(this -> epoll_fd_, EPOLL_CTL_ADD, new_socket, &ev);
  }
  // @todo: remember rsrc recycling 
  // pthread_join(serv_th, NULL);
}

void* Server::reader(void* arg) {
  Server* serv_p = (Server*)arg;
  const uint8_t EVENT_BUF_SZ = 10;
  epoll_event evs[EVENT_BUF_SZ];
  
  while (1) {
    int fd_n = epoll_wait(serv_p -> epoll_fd_, evs, EVENT_BUF_SZ, -1);
    for(size_t i = 0; i < fd_n; ++i) {
      if (evs[i].events & EPOLLIN) {
        // parameters
        struct ParserAdaptorStruct pas = {
          evs[i].data.fd, 
          serv_p
        };
        // new thread for each connection
        pthread_t thd;
        pthread_create(&thd, nullptr, Server::parserAdaptor, (void*)&pas);
        // serv_p -> parser(evs[i].data.fd);
      } else if (evs[i].events & EPOLLHUP) {    
          close(evs[i].data.fd);
      }
    }
  }
  return nullptr;  
}

void Server::parser(ssize_t fd) {
  // fmt::println("parse msg...");      // @todo: repeated log?

  char buffer[this -> BUFFER_SIZE] = {0}; // buffer for reading from socket buf @todo: cant be compiled by clang 14
  std::string msg_buf; // buffer for structuring data
  std::unique_ptr<CRequest::HTTP_Request> req_p(new CRequest::HTTP_Request);

  // deal with header
  std::regex hdr_div("\r\n\r\n"); // divided by CRLF
  std::cmatch res;
  size_t req_msg_len = 0;
  bool hdr_end = false;     

  // timeout handler
  struct timeval timeout;
  timeout.tv_sec = 3;
  timeout.tv_usec = 0;
  socklen_t timeout_len = sizeof(timeout);
  setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, timeout_len);

  // io
  while(1) {      
    ssize_t len_read = recv(fd, buffer, this -> BUFFER_SIZE, 0);
    if(len_read > 0) {
      msg_buf.append(buffer);
      hdr_end = std::regex_search(buffer, res, hdr_div);
    } else if (!hdr_end && len_read <= 0) {    // no responses fo http messages with invalid format
      // fmt::println("kill connection...");
      close(fd);
      return;
    }

    if(hdr_end) {
      const std::string full_hdr(msg_buf + res.prefix().str());
      std::regex find_len("Content-Length:[ ]{0,}(\\d+)");
      std::smatch len_res;
      bool len_found = std::regex_search(full_hdr, len_res, find_len);
      if(len_found) {
        req_msg_len = std::stoi(len_res.str(1));
      }

      std::unique_ptr<std::vector<std::string>> 
        hdr_ptr(CRequest::Utils::split(full_hdr, "\r\n"));
      msg_buf.clear();
      msg_buf.append(res.suffix().str());

      bool is_fst_ln = true;
      for (auto& ln : *hdr_ptr) {
        if(is_fst_ln) {
          std::unique_ptr<std::vector<std::string>>
            fst_ln_ptr(CRequest::Utils::split(ln, " "));
            req_p -> set_fst_hdr_ln((*fst_ln_ptr)[0], (*fst_ln_ptr)[1], 
              (*fst_ln_ptr)[2]);
          is_fst_ln = false;
        }else {
          req_p -> add_hdr_ln(ln);
        }
      }
      break;
    }
  }
  
  // deal with body
  ssize_t bytes_read_cur = 0;
  ssize_t bytes_left = req_msg_len - msg_buf.length();
  if(req_msg_len) {
    while (1) {
      bytes_read_cur += read(fd, buffer, bytes_left);
      bytes_left -= bytes_read_cur;
      
      if(bytes_left) {
        msg_buf.append(buffer);
      }else {
        req_p -> set_body(msg_buf + buffer);
        break;
      }
    }
  }

  // Deal with request and response
  // @todo: request could be cached in a temporary queue 
  CRequest::HTTP_Response* hresp_p;
  Service sv(*req_p);
  std::string addr_v4(CRequest::Utils::getConnAddr(fd));

  if(sv.method_ == "POST") { // GET routers
    if(sv.route_match(hresp_p, fd)) {     
      std::string resp_msg = hresp_p -> to_string();
      send(fd, resp_msg.c_str(), resp_msg.length(), 0);
    } else {
      std::string err_msg = "{\"msg\":\"route invalid\"}";
      hresp_p = new CRequest::HTTP_Response(404, {
        CRequest::Header_Generator::set_content_len(err_msg.length())
      });
      hresp_p -> set_body(err_msg);
      std::string resp_msg = hresp_p -> to_string();
      send(fd, resp_msg.c_str(), resp_msg.length(), 0);
    }
  } else if(sv.method_ == "OPTIONS") { // CORS
    hresp_p = new CRequest::HTTP_Response(200, {
      CRequest::Header_Generator::set_content_len(0),
      CRequest::Header_Generator::set_allow_origin("*"),
      CRequest::Header_Generator::set_allow_methods({"GET", "OPTIONS", "POST"}),
      CRequest::Header_Generator::set_allow_hdrs({"Content-Length", "Content-Type", "Token"})
    });
    Runtime::logger.log(
      {addr_v4, sv.method, "200", "/"}, Runtime::clr_200);
  } else if(sv.method_ == "GET") {
    hresp_p = new CRequest::HTTP_Response(404, {});
    Runtime::logger.log(
      {addr_v4, sv.method, "404", "/invalid"}, Runtime::clr_404);
  }
  if(hresp_p != nullptr) {
    delete hresp_p;
  }
  close(fd); 
  return;
}


void* Server::parserAdaptor(void* arg) {
  struct ParserAdaptorStruct* p = (ParserAdaptorStruct*)arg; 
  p->serv_p->parser(p->fd);
  return nullptr;
}
