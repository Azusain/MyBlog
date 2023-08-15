// unix
#include <dirent.h>
// C++ std
#include <memory>
#include <vector>
#include <string>
#include <sstream>

#include "fmt/core.h"
#include "Utils.h"

#include "json/json.h"
namespace CRequest {

namespace Utils {

std::vector<std::string>* split(const std::string& str, const std::string& delimiter) {
    auto result = new std::vector<std::string>();
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        result -> push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    result -> push_back(str.substr(start, end));
    return result;
}

std::string json2str(const Json::Value& v, bool fmt_output=false) {
  Json::StreamWriterBuilder builder;
  if(!fmt_output) {
      builder["indentation"] = "";
  }
  return Json::writeString(builder, v); // auto RVO by compilor
}


typedef bool(*FileFilter)(const dirent*);


struct DirCloser {
  void operator()(DIR* dir){
    if(dir){
      closedir(dir);
    }
    return;
  }
};

FileLoader::FileLoader(std::string rt_pth)
  :rt_pth(rt_pth) {}

// 
std::vector<std::string> FileLoader::srch_dir(const std::string& rlt_pth,
  FileFilter tf=nullptr, bool log=false) {
  std::string cur_pth(this -> rt_pth + rlt_pth);
  std::vector<std::string> file_pths;
  std::unique_ptr<DIR, DirCloser> dir(opendir(cur_pth.c_str()));
  dirent* dir_itor = nullptr;

  // open dir
  if(!dir){
    fmt::print("Failed to open target diretory {}\n", cur_pth);
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
    // ignore dir named '.' and '..'
    if(!strcmp(".", dir_itor -> d_name) || !strcmp("..", dir_itor -> d_name)) {
      continue; 
    }
    if(tf == nullptr || tf(dir_itor)) {
      file_pths.push_back(dir_itor -> d_name);
      if(log) {
        fmt::print("{} {}\n", file_type_name, dir_itor -> d_name);
      }
    }
  }
  return file_pths;
}


} // namesapce Utils

} // namespace CRequest