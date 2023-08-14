// unix 
#include <dirent.h>
// c++ std
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace CRequest {

namespace Utils {
  // string operation
std::vector<std::string>* split(const std::string& str, const std::string& delimiter);


typedef bool(*FileFilter)(const dirent*);





class FileLoader {
public:
  FileLoader(std::string rt_pth);
  
  std::vector<std::string> srch_dir(const std::string& rlt_pth,
    FileFilter f, bool log=false);

protected:
  std::string rt_pth;
};





} // namespace Utils



} // namesapce CRequest