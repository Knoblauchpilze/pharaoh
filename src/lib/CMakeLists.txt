project (pharaoh_lib)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

#set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library (pharaoh_lib SHARED "")

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/coordinates
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/app
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/game
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/ui
	)

target_sources (pharaoh_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/App.cc
	)

target_link_libraries (pharaoh_lib
	png
	X11
	GL
	pthread
	stdc++fs
	)

target_include_directories (pharaoh_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/app
	${CMAKE_CURRENT_SOURCE_DIR}/coordinates
	${CMAKE_CURRENT_SOURCE_DIR}/ui
	)
