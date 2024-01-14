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

#include "logger.h"
#include "server.h"
#include "CRequest.h"
#include "utils.h"
#include "runtime.h"

#include "http_parser.h"


int main(int, char **) {
  Server s(8080);
  s.Start();
  return 0;
}
