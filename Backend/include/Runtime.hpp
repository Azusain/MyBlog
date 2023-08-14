#include "Logger.h"
#include "PassageLoader.h"
namespace Runtime{
// init logger
Log::Logger logger({20});
Log::Coloraiton field_clr_0{Log::ANSI_TX_WHITE, Log::ANSI_BG_GREEN, 0};

PassageLoader psg_loader("/root/github-repo/MyBlog/Backend");

// bool(*fp)(const dirent*, unsigned char)
bool file_filter_dir(const dirent* dir_itor) {
  return (dir_itor -> d_type) == DT_DIR;
}

// bool(*fp)(const dirent*, unsigned char)
bool file_filter_file(const dirent* dir_itor) {
  return (dir_itor -> d_type) == DT_REG;
}

}; // namespace Runtime

