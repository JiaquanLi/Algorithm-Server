
project(libpointcloudlib)

add_library(PointCloudLib
	src/interactive_icp.cpp
	)

target_include_directories(PointCloudLib PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE src)
target_link_libraries (PointCloudLib ${PCL_LIBRARIES})
