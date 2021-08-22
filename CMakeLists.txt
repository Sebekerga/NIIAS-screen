cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME NIIAS_screen)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(nlohmann_json REQUIRED)

add_library(lidar_mini_lib src/lidar_mini_lib.h src/lidar_mini_lib.cpp)
target_link_libraries(lidar_mini_lib nlohmann_json::nlohmann_json)
target_include_directories(lidar_mini_lib PUBLIC src)
