cmake_minimum_required (VERSION 3.0)

set (PROJECT arbolibrum)

project (ArboLibrumLib)

set (SOURCE_LIB
	src/note.cpp
	src/compression.cpp
	src/decompression.cpp
	src/encryption.cpp
	src/encryption.cpp
	src/readnote.cpp
	src/writenote.cpp)

include_directories (include)

add_library (${PROJECT} SHARED ${HEADERS} ${SOURCE_LIB})
