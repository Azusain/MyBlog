#include <iostream>
#include <regex>
#include <memory>

#include <fmt/core.h>

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
bool Service::route_match(CRequest::HTTP_Response*& hresp_p, ssize_t& fd) {
  std::string addr_v4 (CRequest::Utils::getConnAddr(fd));
  // auto err_resp_p = new CRequest::HTTP_Response(404, {
  //   CRequest::Header_Generator::set_content_len(0)
  // });

  // route match
  if(this -> url == "/login") {              // /login
    std::string usr = this -> hdr_map["usr"];
    std::string passwd = this -> hdr_map["passwd"];
    
    if(this -> authenticate(usr, passwd)) {
      hresp_p = new CRequest::HTTP_Response(200, {
        CRequest::Header_Generator::set_token("QWEwMjAxMTE="),
        CRequest::Header_Generator::set_content_len(0)
      });
      Runtime::logger.log(
        {addr_v4, this -> method, "200", "/login"}, Runtime::clr_200);
        
    }else {
      hresp_p = new CRequest::HTTP_Response(404, {
        CRequest::Header_Generator::set_content_len(0)
      });
      Runtime::logger.log(
        {addr_v4, this -> method, "404", "/login"}, Runtime::clr_404);
    }
    
  } else if(this -> route_match(this->url, "/columns")) {   // /columns
    Json::Value col_json = Runtime::psg_loader.toJson();
    Json::Value cols = col_json["columns"];
    Json::Value ret_json;
    std::string real_route; 
    

    if(this -> url == "/columns") {     // get all
      real_route = "*";
      for(int i = 0; i < cols.size(); ++i) {
        ret_json["columns"].append(cols[i]["title"]);
      }
    }else { // get msg by endpoint
      real_route = this -> url.replace(this->url.find("/columns/"), 9, ""); //@todo: dangerous
      bool found = false;
      for(int i = 0; i < cols.size(); ++i) {
        if(cols[i]["title"].asString() == real_route) {
          found = true;
          ret_json = cols[i];   
          break;
        }
      }
    }
    std::string ret_json_str = CRequest::Utils::json2str(ret_json, false);
    hresp_p = new CRequest::HTTP_Response(200, {
      CRequest::Header_Generator::set_content_len(ret_json_str.length()),
      CRequest::Header_Generator::set_content_type(CRequest::TYPE_APP_JSON),
      CRequest::Header_Generator::set_connection(false),
      CRequest::Header_Generator::set_allow_origin("*")
    });
    hresp_p -> set_body(ret_json_str);

    Runtime::logger.log(
      {addr_v4, this -> method, "200", fmt::format("/columns/{}", real_route)}, Runtime::clr_200);
  } else {
    Runtime::logger.log(
      {addr_v4, this -> method, "404", this->url}, Runtime::clr_404);
    return false;
  }
  return true;
}

bool Service::route_match(const std::string& full_route, std::string&& route) {
  return (full_route.find(route) != std::string::npos);
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