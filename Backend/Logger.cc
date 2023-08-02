// C++ basic
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <unordered_map>

// C++ 11
#include <chrono>

// fmt-io lib
#include <fmt/core.h>

#include  "Logger.h"
namespace Log{

// text color
const uint8_t ANSI_TX_BLACK = 30;
const uint8_t ANSI_TX_RED = 31;
const uint8_t ANSI_TX_GREEN = 32;
const uint8_t ANSI_TX_YELLOW = 33;
const uint8_t ANSI_TX_BLUE = 34;
const uint8_t ANSI_TX_MAGENTA = 35;
const uint8_t ANSI_TX_CYAN = 36;
const uint8_t ANSI_TX_WHITE = 37;
// bg color
const uint8_t ANSI_BG_BLACK = 40;
const uint8_t ANSI_BG_RED = 41;
const uint8_t ANSI_BG_GREEN = 42;
const uint8_t ANSI_BG_YELLOW = 43;
const uint8_t ANSI_BG_BLUE = 44;
const uint8_t ANSI_BG_MAGENTA = 45;
const uint8_t ANSI_BG_CYAN = 46;
const uint8_t ANSI_BG_WHITE = 47;


Logger::Logger(std::vector<uint8_t>&& widths)
  : max_widths(widths){};


void Logger::log(std::vector<std::string>&& field_vals, std::vector<Coloraiton>&& _clrs) {
  std::string output;
  if(field_vals.size() != this -> max_widths.size()){
    throw std::runtime_error("LOGGER: fileds unmatched error");
  }
  // Basic log with time 
  using std::chrono::system_clock;
  time_t now = system_clock::to_time_t(system_clock::now());
  std::stringstream fmt_stm;
  fmt_stm << std::put_time(std::localtime(&now), "%Y/%m/%d - %H:%M:%S");
  output.append(fmt::format("[LOGGER] {} |", fmt_stm.str()));
  // coloration
  for(int i = 0; i < _clrs.size(); ++i) {
    auto res = this -> clrs.insert(std::make_pair(_clrs[i].idx, _clrs[i]));
    // inserting fails. 
    if(!res.second) {
      this -> clrs[_clrs[i].idx].tx_clr = _clrs[i].tx_clr;
      this -> clrs[_clrs[i].idx].bg_clr = _clrs[i].bg_clr;
    }
  }
  // align the text
  for(int i = 0; i < this -> max_widths.size(); ++i) {

    std::string fmt_field_val(this -> str_align(field_vals[i], this -> max_widths[i]));
    auto it = this -> clrs.find(i);
    if(it != this -> clrs.end()){
      Coloraiton c = it -> second;
      fmt_field_val = fmt::format("\033[{};{}m", c.bg_clr, c.tx_clr) 
        + fmt_field_val + "\033[0m";
    }
    output.append(fmt::format("{}|", fmt_field_val));
  }
  fmt::print("{}\n", output);
  return;
};


// align left
std::string Logger::str_align(const std::string& str ,uint8_t max_width) {
  if(str.length() >= max_width) {
    return fmt::format(" {} ", str.substr(0, max_width));
  }
  return fmt::format(" {} ", str + std::string(max_width - str.length(), ' '));
}
  

}; // namespace Log