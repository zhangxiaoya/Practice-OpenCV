cmake_minimum_required(VERSION 2.8)

project(shiTomasiCorner)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(shiTomasiCorner main.cpp)

target_link_libraries(shiTomasiCorner ${OpenCV_LIBS})