#ifndef __UTILS_H
#define __UTILS_H
// unix 
#include <dirent.h>
// c++ std
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// 3rd-parities
#include "json/json.h"

namespace CRequest {

namespace Utils {
  // string operation
std::vector<std::string>* split(const std::string& str, const std::string& delimiter);

typedef bool(*FileFilter)(const dirent*);

std::string json2str(const Json::Value& v, bool fmt_output);

class FileLoader {
public:
  FileLoader(std::string rt_pth);
  
  std::vector<std::string> srch_dir(const std::string& rlt_pth,
    FileFilter f, bool log);

protected:
  std::string rt_pth;
};

std::string getConnAddr(const size_t& fd);

} // namespace Utils

} // namesapce CRequest

#endif