#ifndef __SERVICE_H
#define __SERVICE_H

#include "CRequest.h"

class Service : public CRequest::HTTP_Request {
public:
  
  Service(const CRequest::HTTP_Request& hr);
  
  bool route_match();  

private:
  Service();
  
  bool authenticate();

};


struct Passgae {
  std::string title;
  std::string brief;
};



struct Column {
  std::string              title;
  std::string              brief;
  std::string              img;
  std::vector<Passgae> passgaes;
};



#endif