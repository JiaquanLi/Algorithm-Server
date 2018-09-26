project(app_algorithm_server)
set(TARGET_NAME "algorithm-server")

add_executable(
	${TARGET_NAME}
	Main.cpp
	)
	
target_link_libraries(${TARGET_NAME}
	-rdynamic
	grpclib
)

#get_filename_component(TOOLCHAIN_PATH "${CMAKE_C_COMPILER}" PATH)
#add_custom_command(
#	TARGET ${TARGET_NAME}
#	POST_BUILD
#	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/stripped
#)

#install(TARGETS ${TARGET_NAME} DESTINATION bin)
