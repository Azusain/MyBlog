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

#include "Logger.h"
#include "Server.h"
#include "CRequest.h"
#include "Utils.h"








int main(int, char **) {
  // Server s(8080);
  // s.start();
  CRequest::Utils::FileLoader fl("/root/github-repo/MyBlog/Backend");
  fl.srch_dir("", true);
  return 0;
}
