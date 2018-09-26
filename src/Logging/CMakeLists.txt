project(liblogging LANGUAGES CXX)

add_library(logging
	src/logging.cpp)

target_include_directories(logging PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE src
	)
	
