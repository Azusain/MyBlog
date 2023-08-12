#ifndef __SERVER_H
#define __SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


class Server{
public:
  Server(uint16_t port);
  sockaddr_in    address;
  int8_t         server_fd;
  int32_t        epoll_fd;
  const uint8_t  MAX_CONNECTIONS; 
  const uint16_t BUFFER_SIZE;
  const uint16_t PORT;

  void start();

  static void* reader(void* arg);

  void parser(ssize_t fd);
};

#endif