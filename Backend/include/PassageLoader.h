#ifndef __PASSGAE_LOADER_H
#define __PASSAGE_LOADER_H
#include <string>
#include <vector>

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

class PassageLoader {
public:  
  PassageLoader();


private:
  std::vector<Column> columns;




};








#endif