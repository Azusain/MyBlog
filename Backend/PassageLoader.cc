#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <regex>
#include <map>
#include <memory>

#include "Utils.h"
#include "PassageLoader.h"
#include "Runtime.h"
#include "fmt/core.h"

PassageLoader::PassageLoader(const std::string&& base_path)
  :FileLoader(base_path) {}


bool PassageLoader::load() {
  std::vector<std::string> dirs(
    this -> srch_dir("", Runtime::file_filter_dir, false));
  char rd_buf[500];   // may define a constant for '500' @todo
  for(auto& dir_name : dirs) {
    // read from description in each dir
    int fd = open(fmt::format("{}/{}/brief", 
      this->rt_pth, dir_name).c_str(), O_RDONLY);
    if(fd == -1){
      perror("fail to open text file\n");
    }

    std::string rd_str_buf;
    ssize_t len = 0;
    while((len = read(fd, rd_buf, 500)) > 0) {
      rd_str_buf.append(rd_buf, len);
    }

    std::unique_ptr<std::vector<std::string>> 
      lines_p(CRequest::Utils::split(rd_str_buf, "\n"));
    std::vector<std::string> lines(*lines_p);
    close(fd);
    // structure data
    Column c;
    c.title = dir_name;
    c.brief = lines[0].replace(0, 6, ""); // 'brief:' @todo: maybe optimized with regex
    c.img =  lines[1].replace(0, 4, "");

    std::regex r("(\\w+[.]\\w+):(.{0,})"); 
    std::smatch m;
    std::map<std::string, std::string> file_map;
    // retrieve in list, append details to 'this->columns'
    for (size_t i = 2; i < lines.size(); i++) {
      std::regex_search(lines[i], m, r);
      if(m.str(1) != ""){
        file_map[m.str(1)] = m.str(2);
      }
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
  rt["columns"] = Json::arrayValue;
  for(auto& c : this->columns) {
    
    Json::Value c_json;
    c_json["title"] = c.title;
    c_json["brief"] = c.brief;
    c_json["img"] = c.img;
    for (auto &p : c.passgaes) {
      Json::Value p_json;
      p_json["title"] = p.title;
      p_json["brief"] = p.brief;
      c_json["passages"].append(p_json);
    }
    rt["columns"].append(c_json);
  }
  
  return rt;
}
