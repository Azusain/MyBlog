#include <cstring>
#include "logger.h"
#include "passage_loader.h"

namespace Runtime{
// init logger
Log::Logger logger({15, 3, 3, 25});
Log::Coloraiton field_clr_200{Log::ANSI_TX_WHITE, Log::ANSI_BG_GREEN, 2};
Log::Coloraiton field_clr_404{Log::ANSI_TX_WHITE, Log::ANSI_BG_RED, 2};
Log::Coloraiton field_clr_route{Log::ANSI_TX_YELLOW, Log::ANSI_BG_BLACK, 3};
std::vector<Log::Coloraiton> clr_200 = {Runtime::field_clr_200, Runtime::field_clr_route};
std::vector<Log::Coloraiton> clr_404 = {Runtime::field_clr_404, Runtime::field_clr_route};

PassageLoader psg_loader("/root/github-repo/MyBlog/Backend/blog-src");

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

