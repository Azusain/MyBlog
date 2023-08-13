#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace CRequest {

namespace Utils {
  // string operation
std::vector<std::string>* split(const std::string& str, const std::string& delimiter);

class FileLoader {
public:
  FileLoader(std::string rt_pth);
  
  std::vector<std::string> srch_dir(std::string&& rlt_pth, bool log);

private:
  std::string rt_pth;
};





}



} // namesapce CRequest