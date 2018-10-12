add_library(btstack STATIC IMPORTED GLOBAL)

set(BLUECODE_VERSION 4.2)

set_target_properties(btstack PROPERTIES
	# library's programming language
	IMPORTED_LINK_INTERFACE_LANGUAGES C

	# library's include directory
	INTERFACE_INCLUDE_DIRECTORIES    ${CMAKE_CURRENT_SOURCE_DIR}/include

	# library location
	IMPORTED_LOCATION                ${CMAKE_CURRENT_SOURCE_DIR}/lib/libbluecode.a
	)
