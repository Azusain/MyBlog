#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "CRequest.h"

namespace CRequest {
  enum class State {
    METHOD,
    URL,
    VERSION,
    HEADERS,
    BODY,
    DONE,
    ERR
  };

  class HttpParser {
    public:
    CRequest::HttpRequest request_;

    explicit HttpParser(
      const char *data_src,    
      const size_t kBufferSize = 512,
      const size_t kMaxMsgLength = 4096
    ):
      state_(State::METHOD),
      n_total_read_(0),
      cur_buf_idx_(kBufferSize),
      end_buf_idx_(kBufferSize),
      kBufferSize_(kBufferSize),
      kMaxMsgLength_(kMaxMsgLength)
    {
      io_buffer_.resize(kBufferSize_);
      fin_.open(data_src, std::ios_base::in);
      if (!fin_) {
        std::cout << "failed to open source file as stream";
        std::terminate();
      }
    }

    bool ReadFromFStream() {
      if (!fin_) {
        return false;
      }
      fin_.read(io_buffer_.data(), static_cast<std::streamsize>(kBufferSize_));
      end_buf_idx_ = fin_.gcount();
      return true;
    }

    bool ParseStream() {
      while (true) {
        if (this->state_ == State::ERR) {
          return false;
        } else if (state_ == State::DONE) {
          return true;
        }
        if (cur_buf_idx_ == end_buf_idx_) {
          if (!this->ReadFromFStream()) {
            return false;
          }
          cur_buf_idx_ = 0;
        }
        this->ParseByte();
        ++cur_buf_idx_;
      }
    }

    void ParseByte() {
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
          } else if (cur_char == '\n') {
            state_ = State::ERR;
          }
          msg_buffer_.push_back(cur_char);
          break;

        case State::URL:
          if (cur_char == ' ') {
            request_.url_ = msg_buffer_;
            msg_buffer_.clear();
            state_ = State::VERSION;
            break;
          } else if (cur_char == '\n') {
            state_ = State::ERR;
            break;
          }
          msg_buffer_.push_back(cur_char);
          break;

        case State::VERSION:
          if (cur_char == '\n') {
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
          if (cur_char == '\n') {
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

    private:
    std::vector<char> io_buffer_;
    std::string msg_buffer_;
    State state_;
    size_t end_buf_idx_;
    size_t cur_buf_idx_;
    size_t n_total_read_;
    const size_t kBufferSize_;
    const size_t kMaxMsgLength_;

  //    data source (optional)
    std::fstream fin_;
  };
}