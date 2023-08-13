#include  <iostream>

#include "Service.h"


Service::Service()
  :CRequest::HTTP_Request() {}

Service::Service(const CRequest::HTTP_Request& hreq)
  :CRequest::HTTP_Request(hreq) {}


/**
 * rertun false if request route is invalid
*/

bool Service::route_match() {
  if(this -> url == "/login") {
    // Issue
    std::cout << this -> body << "\n";
    return true;
  }
  return true;
}