#include <unistd.h>

#include "Server.h"
#include "CRequest.h"
#include "utils.h"
#include "Logger.h"
#include <fmt/core.h>


#include <memory>
#include <regex>
#include <sstream>

Server::Server(uint16_t port)
    :MAX_CONNECTIONS(10), BUFFER_SIZE(1024), PORT(port){
    
    // init logger
    Log::Logger logger({20});
    Log::Coloraiton val_0{Log::ANSI_TX_WHITE, Log::ANSI_BG_GREEN, 0};
    logger.log({fmt::format("Server runs on {}", this -> PORT)}, {val_0});

    int addrlen = sizeof(this -> address);
    this -> server_fd = socket(AF_INET, SOCK_STREAM, 0);
    this -> address.sin_family = AF_INET;
    this -> address.sin_addr.s_addr = INADDR_ANY;
    this -> address.sin_port = htons(this -> PORT);        
    
    bind(server_fd, (struct sockaddr *)&(this -> address), sizeof(this -> address));
    
    // iteration server
    while (true) {
        listen(server_fd, this -> MAX_CONNECTIONS);
        ssize_t new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        logger.log({"New request"}, {val_0});
        
        
        service_handler(new_socket);
    }
}


void Server::service_handler(ssize_t fd) {
    // sleep(1);
    char buffer[this -> BUFFER_SIZE] = {0}; // buffer for reading from socket buf
    std::string msg_buf; // buffer for structuring data
    std::unique_ptr<CRequest::HTTP_Request> req_p(new CRequest::HTTP_Request);

    // deal with header
    std::regex hdr_div("\r\n\r\n"); // divided by CRLF
    std::cmatch res;
    size_t req_msg_len = 0;
    bool hdr_end = false;     

    while(1) {
      
      ssize_t len_read = read(fd, buffer, this -> BUFFER_SIZE);

      std::cout << buffer;

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
     * Deal with HTTP_Request obj here... 
     * 
    */
  
    // response to client
    std::string resp_msg = CRequest::HTTP_Response(200, {CRequest::Header_Generator::set_content_len(0)}).to_string();
    send(fd, resp_msg.c_str(), resp_msg.length(), 0);
  
    // end connection

    close(fd);
    return;
}