add_library(digimarc STATIC IMPORTED GLOBAL)
	
set_property(TARGET digimarc 
	PROPERTY INTERFACE_INCLUDE_DIRECTORIES 
		${CMAKE_CURRENT_SOURCE_DIR}/include/DigimarcEmbeddedSystems)

set_property(TARGET digimarc 
	PROPERTY IMPORTED_LOCATION 
		${CMAKE_CURRENT_SOURCE_DIR}/lib/iMX6UL-ARM-Poky/release/libdessdk.a)
