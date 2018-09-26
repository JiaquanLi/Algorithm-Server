
project(libpointcloudlib LANGUAGES CXX)

add_library(pointcloudlib
	src/interactive_icp.cpp
	)

target_include_directories(pointcloudlib 
	PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE src)
target_link_libraries (pointcloudlib ${PCL_LIBRARIES})
