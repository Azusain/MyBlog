#include <cctype>
#include <fmt/core.h>
#include <iostream>
#include <sys/socket.h>
#include <vector>
#include <unordered_map>
#include <fstream>

#include <unistd.h>

#include "CRequest.h"
#include "http_parser.h"

namespace CRequest {

HttpParser::HttpParser(
  const char *data_src,    
  const size_t kBufferSize,
  const size_t kMaxMsgLength
):
  state_(State::METHOD),
  n_total_read_(0),
  cur_buf_idx_(kBufferSize),
  end_buf_idx_(kBufferSize),
  kBufferSize_(kBufferSize),
  kMaxMsgLength_(kMaxMsgLength),
  io_buffer_(kBufferSize)
{
  fin_.open(data_src, std::ios_base::in);
  if (!fin_) {
    std::cout << "failed to open source file as stream";
    std::terminate();
  }
}

HttpParser::HttpParser(
  int fd,
  const size_t kBufferSize,
  const size_t kMaxMsgLength
): 
  fd_(fd),  
  state_(State::METHOD),
  n_total_read_(0),
  cur_buf_idx_(kBufferSize),
  end_buf_idx_(kBufferSize),
  kBufferSize_(kBufferSize),
  kMaxMsgLength_(kMaxMsgLength),
  io_buffer_(kBufferSize)
{
}

bool HttpParser::ReadFromFileStream() {
  if (!fin_) {
    return false;
  }
  fin_.read(io_buffer_.data(), static_cast<std::streamsize>(kBufferSize_));
  end_buf_idx_ = fin_.gcount();
  return true;
}

bool HttpParser::ReadFromSocket() {
  int len = recv(fd_, io_buffer_.data(), kBufferSize_, 0);
  return len > 0;
}

bool HttpParser::ParseSocketStream() {
    while (true) {
    if (state_ == State::ERR) {
      return false;
    } else if (state_ == State::DONE) {
      return true;
    }
    if (cur_buf_idx_ == end_buf_idx_) {
      if (!this->ReadFromSocket()) {
        return false;
      }
      cur_buf_idx_ = 0;
    }
    this->ParseByte();
    ++cur_buf_idx_;
  }
  return false;
}

bool HttpParser::ParseFileStream() {
  while (true) {
    if (state_ == State::ERR) {
      return false;
    } else if (state_ == State::DONE) {
      return true;
    }
    if (cur_buf_idx_ == end_buf_idx_) {
      if (!this->ReadFromFileStream()) {
        return false;
      }
      cur_buf_idx_ = 0;
    }
    this->ParseByte();
    ++cur_buf_idx_;
  }
}

void HttpParser::ParseByte() {
  char cur_char = io_buffer_[cur_buf_idx_];
  // should be ascii encoded except for 'body'!!!
  if((!isascii(cur_char) && state_ != State::BODY) || ++n_total_read_ > kMaxMsgLength_) {
    state_ = State::ERR;
    return;
  }
  std::cout << cur_char;      // @todo -> remove this line after debugging
  switch (state_) {
    case State::METHOD:
      if (cur_char == ' ') {
        if(!request_.set_method(msg_buffer_)) {
          state_ = State::ERR;
          break;
        }
        msg_buffer_.clear();
        state_ = State::URL;
        break;
      }
      msg_buffer_.push_back(cur_char);
      break;

    case State::URL:
      if (cur_char == ' ') {
        request_.url_ = msg_buffer_;
        msg_buffer_.clear();
        state_ = State::VERSION;
        break;
      }
      msg_buffer_.push_back(cur_char);
      break;

    case State::VERSION:
      if(cur_char == '\r') {
        break;
      } else if (cur_char == '\n') {
        if(!request_.set_version(msg_buffer_)) {
          state_ = State::ERR;
          break;
        }
        msg_buffer_.clear();
        state_ = State::HEADERS;
        break;
      } else if (cur_char == ' ') {
        state_ = State::ERR;
        break;
      } else
        msg_buffer_.push_back(cur_char);
      break;

    case State::HEADERS:
      if(cur_char == '\r') {
        break;
      } else if (cur_char == '\n') {
        if (!msg_buffer_.empty()) {
          auto pos = msg_buffer_.find(':');
          if (pos == std::string::npos) {
            state_ = State::ERR;
            break;
          }
          std::string key = msg_buffer_.substr(0, pos);
          std::string val = msg_buffer_.substr(pos + 1, msg_buffer_.length());
          request_.headers_.emplace(key, val);
          if (key == "content-length") {
            request_.body_size_ = stoi(val);
          }
          msg_buffer_.clear();
          break;
        } else {
          state_ = State::BODY;
          break;
        }
      } else if (cur_char == ' ') {
        break;
      }
      msg_buffer_.push_back(static_cast<char>(::tolower(cur_char)));
      break;

    case State::BODY:
      if (request_.headers_.find("content-length") == request_.headers_.end()) {
        state_ = State::DONE;
        break;
      }
      if (request_.body_size_ == msg_buffer_.length() + 1) {
        request_.body_ = msg_buffer_ + cur_char;
        msg_buffer_.clear();
        state_ = State::DONE;
        break;
      }
      this->msg_buffer_.push_back(cur_char);
      break;

    default:
      break;
  }
}

} // namespace CRequest