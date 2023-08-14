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
#include "Runtime.hpp"







// @todo: needs exception handler
int main(int, char **) {
  bool run_or_not = Runtime::psg_loader.load();
  std::cout << std::boolalpha << run_or_not << "\n";
  // Server s(8080);
  // s.start();
  // CRequest::Utils::FileLoader fl("/root/github-repo/MyBlog/Backend");
  // fl.srch_dir("", true);
  // Json::Value jv;
  return 0;
}
