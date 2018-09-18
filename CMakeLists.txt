cmake_minimum_required(VERSION 2.8)
project(AlServer C CXX)

find_package(PCL 1.5 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


add_subdirectory(src/PointCloudLib)
add_subdirectory(src/App)
