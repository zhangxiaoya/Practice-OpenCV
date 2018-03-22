cmake_minimum_required( VERSION 2.8 )
project ( macthBasedFLANN )

# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11" )

# OpenCV
set(OpenCV_DIR /usr/local/opencv3/share/OpenCV)
find_package( OpenCV 3.2 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( matchUseFLANN main.cpp )

# 链接OpenCV库
target_link_libraries( matchUseFLANN ${OpenCV_LIBS} )