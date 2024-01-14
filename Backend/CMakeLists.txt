cmake_minimum_required(VERSION 3.25)
project(Template VERSION 0.0.1)


set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


find_package(fmt CONFIG REQUIRED)

file(GLOB SOURCES "src/*.cc" "src/*.cpp")
file(GLOB INCLUDE_DIR "include")

add_executable(Main ${SOURCES})

target_include_directories(Main PRIVATE ${INCLUDE_DIR})

target_include_directories(Main PRIVATE "/usr/include/jsoncpp" )

target_link_libraries(Main
  fmt::fmt
  jsoncpp
)