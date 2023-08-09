#ifndef __LOGGER_H
#define __LOGGER_H

#include <vector>
#include <string>
#include <unordered_map>

namespace Log {

// text color
extern const uint8_t ANSI_TX_BLACK;
extern const uint8_t ANSI_TX_RED;
extern const uint8_t ANSI_TX_GREEN;
extern const uint8_t ANSI_TX_YELLOW;
extern const uint8_t ANSI_TX_BLUE;
extern const uint8_t ANSI_TX_MAGENTA;
extern const uint8_t ANSI_TX_CYAN;
extern const uint8_t ANSI_TX_WHITE;

// bg color
extern const uint8_t ANSI_BG_BLACK;
extern const uint8_t ANSI_BG_RED;
extern const uint8_t ANSI_BG_GREEN;
extern const uint8_t ANSI_BG_YELLOW;
extern const uint8_t ANSI_BG_BLUE;
extern const uint8_t ANSI_BG_MAGENTA;
extern const uint8_t ANSI_BG_CYAN;
extern const uint8_t ANSI_BG_WHITE;

struct Coloraiton {
  uint8_t tx_clr;
  uint8_t bg_clr;
  uint8_t idx;
};

class Logger {
public:
  Logger(std::vector<uint8_t>&& widths);

  void log(std::vector<std::string>&& field_vals, std::vector<Coloraiton>&& _clrs);

private:
  std::string str_align(const std::string& str ,uint8_t max_width);
  
  std::vector<uint8_t> max_widths;
  std::unordered_map<uint8_t, Coloraiton> clrs;
};

} // namespace Log

#endif