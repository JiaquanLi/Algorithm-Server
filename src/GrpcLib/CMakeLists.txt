# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# cmake build file for C++ helloworld example.
# Assumes protobuf and gRPC have been installed using cmake.
# See cmake_externalproject/CMakeLists.txt for all-in-one cmake build
# that automatically builds all the dependencies before building helloworld.

project(libgrpclib)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



# This branch assumes that gRPC and all its dependencies are already installed
# on this system, so they can be located by find_package().

# Find Protobuf installation
# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

# Proto file
get_filename_component(hw_proto "../../../protos/route_guide.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
#set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/route_guide.pb.cc")
#set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/route_guide.pb.h")
#set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/route_guide.grpc.pb.cc")
#set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/route_guide.grpc.pb.h")
#add_custom_command(
#      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
#      COMMAND ${_PROTOBUF_PROTOC}
#      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
#        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
#        -I "${hw_proto_path}"
#        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
#        "${hw_proto}"
#      DEPENDS "${hw_proto}")

# Include generated *.pb.h files
#include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(grpclib
    src/GrpcServer.cpp
    src/route_guide.grpc.pb.cc
    src/route_guide.pb.cc
    src/route_guide_client.cc
  )


target_include_directories(grpclib 
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE src)

target_link_libraries (grpclib pointcloudlib ${PCL_LIBRARIES} ${_GRPC_GRPCPP_UNSECURE} ${_PROTOBUF_LIBPROTOBUF})


#add_library(gRrpcLib
#    src/GrpcServer.cpp
#  )
#target_include_directories(gRrpcLib PUBLIC
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#  PRIVATE src)
#target_link_libraries (gRrpcLib PointCloudLib ${_GRPC_GRPCPP_UNSECURE}  ${_PROTOBUF_LIBPROTOBUF})


# Targets greeter_[async_](client|server)
#foreach(_target
#    GrpcServer route_guide_client
# )
#  add_library(${_target} "${_target}.cpp"
#    ${hw_proto_srcs}
#    ${hw_grpc_srcs})
#  target_link_libraries(${_target}
#    ${_GRPC_GRPCPP_UNSECURE}

#    ${_PROTOBUF_LIBPROTOBUF}
#  ${PCL_LIBRARIES}
#  PointCloudLib)
#endforeach()

#add_custom_command(
#	TARGET "AlServer"
#	POST_BUILD
#	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/stripped
#	COMMAND mv ${CMAKE_BINARY_DIR}/src/App/AlServer ${CMAKE_BINARY_DIR}/stripped
	
#)
