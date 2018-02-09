cmake_minimum_required(VERSION 3.6)
project(BoundaryDetector)
find_package( OpenCV REQUIRED )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ExtendedMat.cpp ExtendedMat.h)
add_executable(BoundaryDetector ${SOURCE_FILES})
target_link_libraries( BoundaryDetector ${OpenCV_LIBS} )