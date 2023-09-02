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
  char rd_buf[500];   // @todo: define a constant for '500' here 
  for(std::string& dir_name : dirs) {
    // read from description file in each dir
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
    c.img   = lines[1].replace(0, 4, "");
    c.date  = lines[2].replace(0, 5, "");

    std::regex r("(\\w+[.]\\w+):(.{0,}):(.{0,}):(.{0,})"); 
    std::smatch m;
    std::map<std::string, Passgae> file_map;
    // retrieve in list, append details to 'this->columns'
    for (size_t i = 3; i < lines.size(); i++) {
      std::regex_search(lines[i], m, r);
      if(m.str(1) != ""){
        file_map[m.str(1)].brief = m.str(2);
        file_map[m.str(1)].date = m.str(3);
        file_map[m.str(1)].img = m.str(4);
      }
    }
    
    // collect passages from each directory
    auto passages(this -> srch_dir(fmt::format("/{}", dir_name),
       Runtime::file_filter_file, false));
    // leave out images files such as .png .jpg and .gif
    std::regex img_rgx("[.]{0,}.(png|jpg)");
    std::smatch img_m;

    for(auto& p_name: passages) {
      std::regex_search(p_name, img_m, img_rgx);
      if(img_m.str(0) != "") {
        continue;
      }
      Passgae p;
      p.title = p_name;
      auto _p = file_map[p_name];
      p.brief = _p.brief;
      p.date = _p.date;
      p.img = _p.img;
      c.passgaes.push_back(p);
    }
    this -> columns.push_back(c);
  }
  return true;
}

Json::Value PassageLoader::toJson() {
  Json::Value rt;
  rt["columns"] = Json::arrayValue;
  for(auto& c : this->columns) {
    Json::Value c_json;
    c_json["title"] = c.title;
    c_json["brief"] = c.brief;
    c_json["img"] = c.img;
    c_json["date"] = c.date;
    for (auto &p : c.passgaes) {
      Json::Value p_json;
      p_json["title"] = p.title;
      p_json["brief"] = p.brief;
      p_json["date"] = p.date;
      p_json["img"] = p.img;
      c_json["passages"].append(p_json);
    }
    rt["columns"].append(c_json);
  }
  
  return rt;
}
