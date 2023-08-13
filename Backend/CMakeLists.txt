cmake_minimum_required(VERSION 3.0.0)
project(Backend VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 14) # required by GoogleTest

include_directories(
    /usr/include/
    ./include/utils
    ./include/
)

link_directories(
    /usr/lib/
)


add_executable(Backend 
  main.cc 
  Logger.cc 
  Server.cc 
  CRequest.cc 
  Utils.cc 
  Service.cc
  PassageLoader.cc
)


target_link_libraries(Backend
    fmt
    # google_test
)
