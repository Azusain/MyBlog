#ifndef __SERVER_H
#define __SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "service.h"
#include "thpoolcc.h"

class Server;

struct ParserAdaptorStruct {
  int fd;
  Server* serv_p;
};


class Server{
public:
  Server(uint16_t port, uint8_t n_max_conn=10, uint16_t buffer_size=1024, uint8_t n_max_threads=5);

  sockaddr_in    address_;
  int8_t         server_fd_;
  int32_t        epoll_fd_;
  
  const uint8_t  kMaxConnections; 
  const uint16_t kBufferSize;
  const uint16_t kPORT;
  ThreadPoolCC::ThreadPool thpool_;
  void Start();

  static void* Reader(void* arg);
 
  void Parser(ssize_t fd);

  static void* ParserAdaptor(void* arg);
};

#endif