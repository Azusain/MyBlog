#include <cstring>
#include "Logger.h"
#include "PassageLoader.h"

namespace Runtime{
// init logger
Log::Logger logger({20, 3});
Log::Coloraiton field_clr_200{Log::ANSI_TX_WHITE, Log::ANSI_BG_GREEN, 0};
Log::Coloraiton field_clr_404{Log::ANSI_TX_WHITE, Log::ANSI_BG_RED, 0};

PassageLoader psg_loader("/root/github-repo/MyBlog/Backend/testdir");

bool file_filter_dir(const dirent* dir_itor) {
  return (dir_itor -> d_type) == DT_DIR;
}

bool file_filter_file(const dirent* dir_itor) {
  if(!strcmp(dir_itor->d_name, "brief")){
    return false;
  }
  return (dir_itor -> d_type) == DT_REG;
}

}; // namespace Runtime

