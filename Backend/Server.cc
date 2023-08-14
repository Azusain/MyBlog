// unix
#include <unistd.h>
#include <sys/epoll.h>
#include <pthread.h>
// C++ std
#include <memory>
#include <regex>
#include <sstream>
// IO
#include <fmt/core.h>
// proj files
#include "Server.h"
#include "CRequest.h"
#include "Utils.h"
#include "Logger.h"
#include "Service.h"
#include "Runtime.hpp"



Server::Server(uint16_t port)
  :MAX_CONNECTIONS(10), BUFFER_SIZE(1024), PORT(port) {
    this -> server_fd = socket(AF_INET, SOCK_STREAM, 0);
    this -> address.sin_family = AF_INET;
    this -> address.sin_addr.s_addr = INADDR_ANY;
    this -> address.sin_port = htons(this -> PORT);        
}


void Server::start() {
  
  Runtime::logger.log({fmt::format("Server runs on {}", this -> PORT)}, 
    {Runtime::field_clr_0});
  
  // init acceptor
  int addrlen = sizeof(this -> address);
  bind(server_fd, (struct sockaddr *)&(this -> address), sizeof(this -> address));
  listen(server_fd, this -> MAX_CONNECTIONS);
  this -> epoll_fd = epoll_create(1024);

  // init service thread
  // @todo : need threadpool implementations here~
  pthread_t serv_th;
  pthread_create(&serv_th, nullptr, this -> reader, (void*)this);

  while (true) {
    ssize_t new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    
    if(new_socket < 0){
      perror("err accepting socket\n");
      continue;
    }
    Runtime::logger.log({"New request"}, {Runtime::field_clr_0});
    // epoll
    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = new_socket;
    epoll_ctl(this -> epoll_fd, EPOLL_CTL_ADD, new_socket, &ev);
  }
  // @todo: remember rsrc recycling 
  pthread_join(serv_th, NULL);
}


void* Server::reader(void* arg) {
  Server* serv_p = (Server*)arg;
  const uint8_t EVENT_BUF_SZ = 10;
  epoll_event evs[EVENT_BUF_SZ];
  
  while (1) {
    int fd_n = epoll_wait(serv_p -> epoll_fd, evs, EVENT_BUF_SZ, -1);
    for(size_t i = 0; i < fd_n; ++i) {
      serv_p -> parser(evs[i].data.fd);
    }
  }
  return nullptr;  
}


void Server::parser(ssize_t fd) {
  // sleep(1);
  char buffer[this -> BUFFER_SIZE] = {0}; // buffer for reading from socket buf @todo: cant be compiled by clang 14
  std::string msg_buf; // buffer for structuring data
  std::unique_ptr<CRequest::HTTP_Request> req_p(new CRequest::HTTP_Request);

  // deal with header
  std::regex hdr_div("\r\n\r\n"); // divided by CRLF
  std::cmatch res;
  size_t req_msg_len = 0;
  bool hdr_end = false;     

  while(1) {      
    ssize_t len_read = read(fd, buffer, this -> BUFFER_SIZE);

    hdr_end = std::regex_search(buffer, res, hdr_div);
    if(hdr_end) {
      const std::string full_hdr(msg_buf + res.prefix().str());
      std::regex find_len("Content-Length:(\\d+)");
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
    if(len_read > 0) {
      msg_buf.append(buffer);
    }
  }
  
  // deal with body
  ssize_t bytes_read_cur = 0;
  ssize_t bytes_left = req_msg_len;
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

  /**
   * 
   * Deal with HTTP_Request obj here...  req_p -> ?
   * 
  */

  Service sv(*req_p);
  int stat_code = 404;
  
  std::string resp_msg;
  
  if(sv.route_match(resp_msg)) {
    send(fd, resp_msg.c_str(), resp_msg.length(), 0);
  } else {
    std::string err_msg = CRequest::HTTP_Response(
    stat_code, {CRequest::Header_Generator::set_content_len(0)}).to_string();
    send(fd, resp_msg.c_str(), err_msg.length(), 0);
  }

  // response to client
  
  

  // end tcp
  // Non-Persistent HTTP
  close(fd); 
  return;
}