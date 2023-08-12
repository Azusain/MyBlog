#ifndef  __REQUEST_H
#define  __REQUEST_H
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>


namespace CRequest {

extern std::unordered_map<uint16_t, std::string> STATUS_CODES;   // why it cant be const?
extern const std::unordered_set<std::string> HTTP_METHODS;
extern const std::string  CONNECTION_CLOSE;
extern const std::string  CONNECTION_KEEP_ALIVE;
// MIME Type down below:
extern const std::string  TYPE_APP_JSON;
extern const std::string  TYPE_APP_URLENCODED;
extern const std::string  TYPE_APP_XML;
extern const std::string  TYPE_APP_OCTET;
extern const std::string  TYPE_TEXT_HTML;
extern const std::string  TYPE_TEXT_PLAIN;
extern const std::string  TYPE_IMG_PNG;
extern const std::string  TYPE_IMG_JPEG;
// HTTP Version, as now it only supports HTTP 1.1
extern const std::string  HTTP_VERSION_01;
extern const std::string  HTTP_VERSION_011;
extern const std::string  HTTP_VERSION_02;
extern const std::string  HTTP_VERSION_03;


namespace Header_Generator{
  std::string set_cookie(std::string, std::string);

  std::string set_connection(bool);

  std::string set_content_type(std::string);

  std::string set_content_len(size_t len);

  // default: User-Agent, Content-Type, Host
} // namespace Header_Generator



class HTTP_Message{
public:
  HTTP_Message();
  
  HTTP_Message(const std::vector<std::string>& hdr_lns);
  
  // virtual void set_fst_hdr_ln() = 0; what happened to this line of codes?

  void add_hdr_ln(std::string hdr_ln);

  void set_body(std::string body_str);

protected:
  std::vector<std::string> header_lines;
  std::string              body;
};


class HTTP_Response : public HTTP_Message {
public:
    HTTP_Response();

    HTTP_Response(uint16_t stat_code, const std::vector<std::string>& hdr_lns);
    
    void set_fst_hdr_ln(uint16_t stat_code, std::string ver);

    std::string  to_string();
private:
    uint16_t     status_code;
    std::string  version;
};


class HTTP_Request : public HTTP_Message {
public:

    HTTP_Request();

    HTTP_Request(std::string method, std::string url, 
      const std::vector<std::string>& hdr_lns);
    
    void set_fst_hdr_ln(std::string method, std::string url, std::string ver);

    std::string  to_string();
protected:
    std::string  method;
    std::string  url;
    std::string  version;
};

}; // namespace CRequest

#endif