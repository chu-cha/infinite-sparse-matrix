
cmake_minimum_required(VERSION 3.5)

project(infinite_matrix )

add_executable(infinite_matrix main.cpp )

set (ALL_SOURCES infinite_matrix)

set_target_properties(${ALL_SOURCES} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

foreach(s ${ALL_SOURCES})
	if (MSVC)
		target_compile_options(${s} PRIVATE
			/W4
		)
		
	else ()
		target_compile_options(${s} PRIVATE
			-Wall 
		)
	endif()
endforeach()

install(TARGETS infinite_matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

