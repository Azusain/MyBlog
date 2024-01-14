#include "CRequest.h"
#include <string>

namespace CRequest {

  std::unordered_map<INT16, std::string> kStatusCode = {
    {100, "Continue"},
    {101, "Switching Protocols"},
    {200, "OK"},
    {201, "Created"},
    {202, "Accepted"},
    {203, "Non-Authoritative Information"},
    {204, "No Content"},
    {205, "Reset Content"},
    {206, "Partial Content"},
    {300, "Multiple Choices"},
    {301, "Moved Permanently"},
    {302, "Found"},
    {303, "See Other"},
    {304, "Not Modified"},
    {305, "Use Proxy"},
    {307, "Temporary Redirect"},
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {402, "Payment Required"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {405, "Method Not Allowed"},
    {406, "Not Acceptable"},
    {407, "Proxy Authentication Required"},
    {408, "Request Timeout"},
    {409, "Conflict"},
    {410, "Gone"},
    {411, "Length Required"},
    {412, "Precondition Failed"},
    {413, "Payload Too Large"},
    {414, "URI Too Long"},
    {415, "Unsupported Media Type"},
    {416, "Range Not Satisfiable"},
    {417, "Expectation Failed"},
    {426, "Upgrade Required"},
    {500, "Internal Server Error"},
    {501, "Not Implemented"},
    {502, "Bad Gateway"},
    {503, "Service Unavailable"},
    {504, "Gateway Timeout"},
    {505, "HTTP Version Not Supported"},
  };

  const std::unordered_set<std::string> kHttpMethods = {
    "GET",
    "POST",
    "OPTIONS",
    "PUT",
    "DELETE",
    "HEAD",
    "TRACE",
    "PATCH",
    "CONNECT"
  };

  const std::string kConnectionClose = "Close";
  const std::string kConnectionKeepAlive = "keep-alive";
  const std::string kTypeAppJson = "application/json";
  const std::string kTypeAppUrlencoded = "application/x-www-form-urlencoded";
  const std::string kTypeAppXml = "application/xml";
  const std::string kTypeAppOctet = "application/octet-stream";
  const std::string kTypeTextHtml = "text/html";
  const std::string kTypeTextPlain = "text/plain";
  const std::string kTypeImgPng = "image/png";
  const std::string kTypeImgJpeg = "image/jpeg";
  const std::string kHttpVersion011 = "HTTP/1.1";

// Header generator
  std::string Header_Generator::set_cookie(std::string key, std::string val) {
    return FORMAT("Set-Cookie:{0}={1}", key, val);
  }

  std::string Header_Generator::set_connection(bool flag) {
    return FORMAT("Connection:{}", flag ? kConnectionKeepAlive : kConnectionClose);
  }

  std::string Header_Generator::set_content_type(std::string content_type) {
    return FORMAT("Content-Type:{}", content_type);
  }

  std::string Header_Generator::set_content_len(size_t len) {
    return FORMAT("Content-Length:{}", len);
  }

  std::string Header_Generator::set_token(std::string token) {
    return FORMAT("Token:{}", token);
  }

  std::string Header_Generator::set_allow_origin(std::string origin) {
    return FORMAT("Access-Control-Allow-Origin:{}", origin);
  }

  std::string Header_Generator::set_allow_hdrs(std::vector<std::string> hdrs) {
    std::string allow_hdrs;
    for (size_t i = 0; i < hdrs.size(); ++i) {
      allow_hdrs.append(hdrs[i]);
      if (i != (hdrs.size() - 1)) {
        allow_hdrs.append(",");
      }
    }
    return std::move(allow_hdrs);
  }

  std::string Header_Generator::set_allow_methods(std::vector<std::string> methods) {
    std::string allow_methods;
    for (size_t i = 0; i < methods.size(); ++i) {
      allow_methods.append(methods[i]);
      if (i != (methods.size() - 1)) {
        allow_methods.append(",");
      }
    }
    return std::move(allow_methods);
  }

// CRequest Main Classes
  HttpMessage::HttpMessage():
    body_size_(-1)
  {};

  void HttpMessage::set_body(std::string body_str) {
    body_ = std::move(body_str);
  }

  HttpRequest::HttpRequest() = default;

  HttpResponse::HttpResponse(
    INT16 status_code,
    const std::vector<std::string> &header_lines
  ):
    status_code_(status_code),
    version_(kHttpVersion011)
  {}

  bool HttpRequest::set_method(const std::string &method) {
    bool is_valid = false;
    for(auto& m : kHttpMethods) {
      if(method == m) {
        is_valid = true;
        break;
      }
    }
    if(is_valid) {
      method_ = method;
    }
    return is_valid;
  }

  bool HttpRequest::set_version(const std::string &version) {
    if(version != kHttpVersion011) {
      return false;
    }
    version_ = version;
    return true;
  }


} // namespace CRequest