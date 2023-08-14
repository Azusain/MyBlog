#include "CRequest.h"
#include <string>
#include <sstream>
#include <fmt/core.h>



namespace CRequest {

std::unordered_map<uint16_t, std::string> STATUS_CODES = { 
  {200, "OK"},
  {301, "Moved Permanently"},
  {400, "Bad Request"},
  {404, "Not Found"},
  {505, "HTTP Version Not Supported"},
}; 

const std::unordered_set<std::string> HTTP_METHODS = {
  "GET", "POST", "OPTIONS", "PUT", "DELETE"
};



const std::string  CONNECTION_CLOSE = "Close";
const std::string  CONNECTION_KEEP_ALIVE = "keep-alive";
const std::string  TYPE_APP_JSON = "application/json";
const std::string  TYPE_APP_URLENCODED = "application/x-www-form-urlencoded";
const std::string  TYPE_APP_XML = "application/xml";
const std::string  TYPE_APP_OCTET = "application/octet-stream";
const std::string  TYPE_TEXT_HTML = "text/html";
const std::string  TYPE_TEXT_PLAIN = "text/plain";
const std::string  TYPE_IMG_PNG = "image/png";
const std::string  TYPE_IMG_JPEG = "image/jpeg";


const std::string HTTP_VERSION_011 = "HTTP/1.1";




// Header generator

// HTTPOnly? Path?


std::string Header_Generator::set_cookie(std::string key, std::string val){
  return fmt::format("Set-Cookie:{0}={1}", key, val);
}

std::string Header_Generator::set_connection(bool flag){
  return fmt::format("Connection:{}", flag ? CONNECTION_KEEP_ALIVE : CONNECTION_CLOSE);
}

std::string Header_Generator::set_content_type(std::string content_type) {
  return fmt::format("Content-Type:{}", content_type);
}

std::string Header_Generator::set_content_len(size_t len) {
  return fmt::format("Content-Length:{}", len);
}


HTTP_Message::HTTP_Message(){}

HTTP_Message::HTTP_Message(const std::vector<std::string>& header_lines)
  : header_lines(header_lines){}


void HTTP_Message::set_body(std::string body_str) {
  this -> body = body_str;
}


void HTTP_Message::add_hdr_ln(std::string hdr_ln) {
  this -> header_lines.push_back(hdr_ln);
  return;
}



HTTP_Request::HTTP_Request(){}


HTTP_Request::HTTP_Request(std::string method, std::string url,
  const std::vector<std::string>& header_lines)
  :HTTP_Message(header_lines), method(method), url(url) {
    // validation checks here
    if(HTTP_METHODS.find(method) == HTTP_METHODS.end()) {
      /**
       * reclaimation is needed here~
       * */ 
      throw std::runtime_error("method invaild");
    }

  }


std::string HTTP_Request::to_string() {
    std::string req_msg;
    req_msg.append(
      fmt::format("{} {} {}\n", this -> method, this -> url, HTTP_VERSION_011)
    );
    for (auto &&header_line : this -> header_lines){
        req_msg.append(header_line + "\r\n");
    }
    req_msg.append("\r\n\r\n");
    return req_msg.append(this -> body);
}


 HTTP_Response::HTTP_Response(uint16_t status_code, const std::vector<std::string>& header_lines)
    :HTTP_Message(header_lines), status_code(status_code), version(HTTP_VERSION_011){}

std::string HTTP_Response::to_string(){
    std::string res_msg;
    res_msg.append(fmt::format("{} {} {}\n", this -> version, this -> status_code, 
       STATUS_CODES[this -> status_code]));

    for (auto &&header_line : this -> header_lines){
        res_msg.append(header_line + "\r\n");
    }
    res_msg.append("\r\n\r\n");
    return res_msg.append(this -> body);
}

void HTTP_Request::set_fst_hdr_ln(std::string method, std::string url, 
  std::string ver) {
  this -> method = method;
  this -> url = url;
  this -> version = ver;
  return;
}








} // namespace CRequest