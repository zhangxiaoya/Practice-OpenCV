cmake_minimum_required(VERSION 3.5)
project(CascadeCalssifier)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(CascadeCalssifier main.cpp)

target_link_libraries(CascadeCalssifier ${OpenCV_LIBS})