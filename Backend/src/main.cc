// // Unix C
// #include <unistd.h>
// #include <sys/epoll.h>
// // C++ basic
#include <iostream>
// #include <vector>
// #include <string>
// #include <exception>
// #include <ctime>
// #include <iomanip>
// #include <sstream>
// #include <unordered_map>

// // C++ 11
// #include <memory> // unique_ptr<T>
// #include <chrono>
// #include <regex>


// // fmt-io lib
// #include <fmt/core.h>
// #include <fmt/ranges.h>

// // jsoncpp lib
// #include <json/value.h>

// #include "logger.h"
// #include "server.h"
// #include "CRequest.h"
// #include "utils.h"
// #include "runtime.h"

#include "thpoolcc.h"

// +------------------------- test --------------------------+

void* test_routine(void* arg) {
  int range = *static_cast<int*>(arg);
  int sum = 0;
  for(int i = 0; i < range; ++i) {
    sum += i;
  }
  std::cout << std::to_string(sum).c_str() << "\n";
  return nullptr;
}




// @todo: needs exception handler
// @todo: regex wrapper
int main(int, char **) {
  // load passgaes from localfile;
  // bool succeed_load = Runtime::psg_loader.load();
  
  // Server s(8080);
  // s.start();
  std::cout << "HelloWorld\n";
  
  ThreadPoolCC::ThreadPool thpool(3);
  
  int range = 1000000;
  for (int i = 0; i < 10; i++) {
    thpool.addWork(test_routine, &range);
  }
  
  thpool.wait(1);
  thpool.destroy();


  return 0;
}
