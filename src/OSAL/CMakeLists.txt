project(libosal LANGUAGES CXX)

add_library(osal
	src/realtime.cpp
	src/timeout.cpp
	src/exception-log.cpp
	src/WakeupTimerList.cpp
	)

target_include_directories(osal PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE src)

target_link_libraries(osal logging helpers)
