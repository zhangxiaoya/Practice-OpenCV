cmake_minimum_required( VERSION 2.8)

project(findHomoGrapgy)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(findHomoGraphy main.cpp)

target_link_libraries(findHomoGraphy ${OpenCV_LIBS})