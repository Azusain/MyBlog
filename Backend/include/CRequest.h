#ifndef  __REQUEST_H
#define  __REQUEST_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

#include <regex>

#ifdef __linux__
  #define INT16 uint16_t
  #include <fmt/core.h>
  #define FORMAT fmt::format
#else
  #include <windows.h>
  #include <format>
  #define FORMAT std::format
#endif

namespace CRequest {
  extern std::unordered_map<INT16, std::string> kStatusCode;   // why it cant be const?
  extern const std::unordered_set<std::string> kHttpMethods;
  extern const std::string kConnectionClose;
  extern const std::string kConnectionKeepAlive;
// MIME Type down below:
  extern const std::string kTypeAppJson;
  extern const std::string kTypeAppUrlencoded;
  extern const std::string kTypeAppXml;
  extern const std::string kTypeAppOctet;
  extern const std::string kTypeTextHtml;
  extern const std::string kTypeTextPlain;
  extern const std::string kTypeImgPng;
  extern const std::string kTypeImgJpeg;
// HTTP Version, as now it only supports HTTP 1.1
  extern const std::string kHttpVersion01;
  extern const std::string kHttpVersion011;
  extern const std::string kHttpVersion02;
  extern const std::string kHttpVersion03;

  namespace Header_Generator {
    std::string set_cookie(std::string, std::string);

    std::string set_connection(bool);

    std::string set_content_type(std::string);

    std::string set_content_len(size_t len);

    std::string set_token(std::string token);

    std::string set_allow_origin(std::string origin);

    std::string set_allow_hdrs(std::vector<std::string> hdrs);

    std::string set_allow_content_type(std::string origin);

    std::string set_allow_methods(std::vector<std::string> methods);

    std::string set_allow_credentials(std::string origin);

    // default: User-Agent, Host
  } // namespace Header_Generator

  class HttpMessage {
    public:
    HttpMessage();

    // virtual void set_fst_hdr_ln() = 0; what happened to this line of codes?

    void set_body(std::string body_str);

    std::unordered_map<std::string, std::string> headers_;
    std::string body_;
    size_t body_size_;

  };

  class HttpResponse : public HttpMessage {
    public:
    HttpResponse(INT16 stat_code, const std::vector<std::string> &hdr_lns);

    INT16 status_code_;

    private:
    std::string version_;
  };


  class HttpRequest : public HttpMessage {
    public:
    HttpRequest();

    bool set_method(const std::string &method);

    bool set_version(const std::string &version);

    std::string method_;
    std::string url_;
    std::string version_;
  };

}; // namespace CRequest

#endif