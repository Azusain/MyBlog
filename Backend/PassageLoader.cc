#include "PassageLoader.h"
#include "Runtime.h"


PassageLoader::PassageLoader(const std::string&& base_path)
  :FileLoader(base_path) {}


bool PassageLoader::load() {
  std::vector<std::string> dirs(
    this -> srch_dir("", Runtime::file_filter_dir, true));
  
  for(auto& dir_name : dirs) {
    Column c;
    c.title = dir_name;
    c.brief = "I am just a brief";
    c.img = "no images here";
    
    auto passages(this -> srch_dir(
      dir_name, Runtime::file_filter_file, false));
    for(auto& p_name: passages) {
      Passgae p;
      p.title = p_name;
      p.brief = "I am just a brief from a passage";
      c.passgaes.push_back(p);
    }
    this -> columns.push_back(c);
  }
  return true;
}

// @todo
Json::Value toJson() {
  Json::Value rt;
  return rt;
}
