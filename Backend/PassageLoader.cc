#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <regex>
#include <map>

#include "Utils.h"
#include "PassageLoader.h"
#include "Runtime.h"
#include "fmt/core.h"

PassageLoader::PassageLoader(const std::string&& base_path)
  :FileLoader(base_path) {}


bool PassageLoader::load() {
  std::vector<std::string> dirs(
    this -> srch_dir("", Runtime::file_filter_dir, true));
  char rd_buf[500];   // may define a constant for '500'
  for(auto& dir_name : dirs) {
    // read from description in each dir
    int fd = open(fmt::format("{}/{}/brief", this->rt_pth, dir_name).c_str(), O_RDONLY);
    if(fd == -1){
      perror("fail to open text file\n");
    }

    std::string rd_str_buf(rd_buf);
    ssize_t len = 0;
    while((len = read(fd, rd_buf, 500)) > 0) {
      rd_str_buf.append(rd_buf, len);
    }
    std::vector<std::string> lines(*CRequest::Utils::split(rd_str_buf, "\n"));
    
    // structure data
    Column c;
    c.title = dir_name;
    c.brief = lines[0].replace(lines[0].begin(), lines[0].end(), "brief:", "");
    c.img =  lines[1].replace(lines[1].begin(), lines[1].end(), "img:", "");

    std::regex r("(\\w+[.]\\w+):(.{0,})"); 
    std::smatch m;
    std::map<std::string, std::string> file_map;
    // retrieve in list
    for (size_t i = 2; i < lines.size(); i++) {
      std::regex_search(lines[i], m, r);
      file_map[m.str(1)] = m.str(2);
    }
    
    auto passages(this -> srch_dir(fmt::format("/{}", dir_name),
       Runtime::file_filter_file, false));
    for(auto& p_name: passages) {
      Passgae p;
      p.title = p_name;
      p.brief = file_map[p_name];
      c.passgaes.push_back(p);
    }
    this -> columns.push_back(c);
  }
  return true;
}

// @todo
Json::Value PassageLoader::toJson() {
  Json::Value rt;
  for(auto& c : this -> columns) {
    // rt["columns"].insert(c.title); @bug
  }
  return rt;
}
