#ifndef __SERVICE_H
#define __SERVICE_H

#include "CRequest.h"
#include <map>


class Service : public CRequest::HTTP_Request {
public:
  
  Service(const CRequest::HTTP_Request& hr);
  
  bool route_match(CRequest::HTTP_Response*& hresp_p, ssize_t& fd);  

  bool route_match(const std::string&, std::string&&);

  bool authenticate(std::string&);
  
  bool authenticate(std::string&, std::string&);

  std::map<std::string, std::string> hdr_map;

private:
  Service();
  
};


#endif