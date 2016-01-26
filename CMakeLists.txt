cmake_minimum_required (VERSION 3.0)
set (PROJECT arbolibrum)
project (ArboLibrum)

set (REQUIRED_LIBRARIES arbolibrum)

set (SOURCE_EXE src/main.cpp)
include_directories (src/lib
	src/lib/compression
	src/lib/encryption src/lib/fileio)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        set(CMAKE_BUILD_TYPE Release)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Release/bin )
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Release/lib )
else ()
	set(CMAKE_BUILD_TYPE Debug)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Debug/bin )
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Debug/lib )
endif ()

add_subdirectory (src/lib)
add_executable (main ${HEADERS} ${SOURCE_EXE})
target_link_libraries (main ${REQUIRED_LIBRARIES})
