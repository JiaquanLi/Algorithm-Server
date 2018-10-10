cmake_minimum_required(VERSION 2.8)
project(ALGORITHM_SERVER)

find_package(PCL 1.5 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

add_subdirectory(libs/DCL)
add_subdirectory(src/Helpers)
add_subdirectory(src/OSAL)
add_subdirectory(src/Logging)
add_subdirectory(src/PointCloudLib)
add_subdirectory(src/GrpcLib)
add_subdirectory(src/Main)

