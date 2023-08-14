#ifndef __PASSAGE_LOADER_H
#define __PASSAGE_LOADER_H
#include <string>
#include <vector>

#include <json/json.h> // jsoncpp lib

#include "Utils.h"

struct Passgae {
  std::string title;
  std::string brief;
};


struct Column {
  std::string              title;
  std::string              brief;
  std::string              img;
  std::vector<Passgae>     passgaes;
};

class PassageLoader : public CRequest::Utils::FileLoader {
public:  
  PassageLoader(const std::string&& base_path);

  bool load();

  Json::Value toJson();

private:
  std::vector<Column> columns;
};








#endif