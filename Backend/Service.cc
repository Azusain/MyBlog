#include  <iostream>

#include "Service.h"
#include "Runtime.hpp"

Service::Service()
  :CRequest::HTTP_Request() {}



Service::Service(const CRequest::HTTP_Request& hreq)
  :CRequest::HTTP_Request(hreq) {}





/**
 * rertun true if request route is valid, otherwise
 * return false and the buf will be set to null   
*/




bool Service::route_match(std::string& buf) {
  if(this -> url == "/login") {
    Runtime::logger.log({"/login"}, {Runtime::field_clr_0});
  }else if(this -> url == "/getPassages") {
    Runtime::logger.log({"/getPassages"}, {Runtime::field_clr_0});
  }else {
    return false;
  }
  return true;
}