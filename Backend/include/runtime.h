#ifndef __RUNTIME_H
#define __RUNTIME_H
#include "logger.h"
#include "passage_loader.h"

namespace Runtime{
// init logger
extern Log::Logger logger;
extern Log::Coloraiton field_clr_route;
extern Log::Coloraiton field_clr_200;
extern Log::Coloraiton field_clr_404;
extern std::vector<Log::Coloraiton> clr_200;
extern std::vector<Log::Coloraiton> clr_404;

extern PassageLoader psg_loader;

// bool(*fp)(const dirent*, unsigned char)
bool file_filter_dir(const dirent* dir_itor);

// bool(*fp)(const dirent*, unsigned char)
bool file_filter_file(const dirent* dir_itor);

}; // namespace Runtime

#endif