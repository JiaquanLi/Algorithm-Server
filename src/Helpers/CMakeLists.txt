project(libhelpers LANGUAGES CXX)

add_library(helpers
	src/bitstring.cpp
	src/crc.cpp
	src/dec-timestamp.cpp
	src/file-utilities.cpp
	src/hstring.cpp
	src/htime.cpp
	src/hwstring.cpp
	src/makepath.c
	src/string-utilities.cpp
	src/system.cpp
	src/tinystr.cpp
	src/tinyxml.cpp
	src/tinyxmlerror.cpp
	src/tinyxmlparser.cpp
	src/backtrace.cpp
	src/sha_256.cpp
	)

target_include_directories(helpers PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE src
	)

target_link_libraries(helpers dcl logging)

