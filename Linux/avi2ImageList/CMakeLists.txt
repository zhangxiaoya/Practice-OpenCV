cmake_minimum_required(VERSION 3.10)
project(avi2ImageList)

set(CMAKE_CXX_STANDARD 11)
SET(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

# OpenCV
SET(OpenCV_DIR /usr/loca/opencv3/share/OpenCV)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})
link_directories(${OpenCV_LIBRARY_DIR})


add_executable(avi2ImageList main.cpp)
target_link_libraries(avi2ImageList ${OpenCV_LIBS})