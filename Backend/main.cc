// Unix C
#include <unistd.h>
#include <dirent.h>

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

// fmt-io lib
#include <fmt/core.h>
#include <fmt/ranges.h>

#include "Logger.h"
#include "Server.h"
#include "CRequest.h"

std::string ROOT_PATH = "../";


struct DirCloser {
  void operator()(DIR* dir){
    if(dir){
      closedir(dir);
    }
    return;
  }
};

void scan_blogs_dir(std::string base_path){
  std::unique_ptr<DIR, DirCloser> dir(opendir(base_path.c_str()));
  dirent* dir_itor = nullptr;

  // open dir
  if(!dir){
    fmt::print("Failed to open target diretory {}\n", base_path);
  }
  // scan dir
  while((dir_itor = readdir(dir.get())) != NULL){
    u_int8_t file_type = dir_itor -> d_type;
    std::string file_type_name;
    if(file_type == DT_REG){
      file_type_name = "file";
    }else if(file_type == DT_DIR) {
      file_type_name = "dir";
    }
    fmt::print("{} {}\n", file_type_name, dir_itor -> d_name);
  }


  return;
}





int main(int, char **) {
  Server s;

  return 0;
}
