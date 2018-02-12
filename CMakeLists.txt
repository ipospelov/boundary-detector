cmake_minimum_required(VERSION 3.6)
project(BoundaryDetector)
find_package( OpenCV REQUIRED )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Sources/main.cpp Sources/ExtendedMat.cpp Sources/ExtendedMat.h Sources/GanglionLayer.cpp Sources/GanglionLayer.h Sources/CortexLayer.cpp Sources/CortexLayer.h Sources/ConeLayer.cpp Sources/ConeLayer.h)
add_executable(BoundaryDetector ${SOURCE_FILES})
target_link_libraries( BoundaryDetector ${OpenCV_LIBS} )