#include <iostream>
#include <regex>
#include <memory>

#include "Service.h"
#include "Runtime.h"


Service::Service()
  :CRequest::HTTP_Request() {}



Service::Service(const CRequest::HTTP_Request& hreq)
  :CRequest::HTTP_Request(hreq) {
    std::regex r("([a-zA-Z-]{0,}):[ ]{0,}(.{0,})");
    std::smatch m;
    for(auto& ln: this -> header_lines) {
      std::regex_search(ln, m, r);
      this -> hdr_map[m.str(1)] =  m.str(2);
    }
  }


/**
 * rertun true if request route is valid, otherwise
 * return false and the buf will be set to null   
*/


bool Service::route_match(CRequest::HTTP_Response* hresp_p) {
  // auto err_resp_p = new CRequest::HTTP_Response(404, {
  //   CRequest::Header_Generator::set_content_len(0)
  // });

  // route match
  if(this -> url == "/login") {
    std::string usr = this -> hdr_map["usr"];
    std::string passwd = this -> hdr_map["passwd"];
    
    if(this -> authenticate(usr, passwd)) {
      hresp_p = new CRequest::HTTP_Response(200, {
        CRequest::Header_Generator::set_token("QWEwMjAxMTE="),
        CRequest::Header_Generator::set_content_len(0)
      });
      Runtime::logger.log({"/login", "200"}, {Runtime::field_clr_200});
    }else {
      Runtime::logger.log({"/login", "404"}, {Runtime::field_clr_404});
      return false;
    }

  }else if(this -> url == "/getPassages") {
    Runtime::logger.log({"/getPassages"}, {Runtime::field_clr_200});
  }
  return true;
}

// by usr and passwd @todo: should be transfered to database
bool Service::authenticate(std::string& usr, std::string& passwd) {
  if(usr == "Azusa" && passwd == "Aa020111") {
    return true;
  }
  return false;
}


// by token
bool Service::authenticate(std::string& token) {
  if(token == "QWEwMjAxMTE=") {
    return true;
  }
  return false;
}