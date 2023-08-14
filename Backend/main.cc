// Unix C
#include <unistd.h>
#include <sys/epoll.h>
// C++ basic
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <unordered_map>

// C++ 11
#include <memory> // unique_ptr<T>
#include <chrono>
#include <regex>


// fmt-io lib
#include <fmt/core.h>
#include <fmt/ranges.h>
// jsoncpp lib
#include <json/value.h>


#include "Logger.h"
#include "Server.h"
#include "CRequest.h"
#include "Utils.h"
#include "Runtime.h"





// @todo: needs exception handler
int main(int, char **) {
  bool succeed_load = Runtime::psg_loader.load();
  std::cout << std::boolalpha << succeed_load << "\n";
  // Server s(8080);
  // s.start();
  // CRequest::Utils::FileLoader fl("/root/github-repo/MyBlog/Backend");
  // fl.srch_dir("", true);
  // Json::Value jv;
  return 0;
}
