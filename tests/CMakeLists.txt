cmake_minimum_required (VERSION 3.7)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

#set (CMAKE_VERBOSE_MAKEFILE ON)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

project(pharaoh_tests LANGUAGES CXX)

find_package (Eigen3 3.4 REQUIRED NO_MODULE)
find_package (GTest REQUIRED)

add_executable(pharaoh-tests)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/unit
	)

target_sources (pharaoh-tests PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cc
	)

target_include_directories (pharaoh-tests PUBLIC
	${GTEST_INCLUDE_DIRS}
	)

target_link_libraries(pharaoh-tests
	core_utils
	pharaoh_lib
	Eigen3::Eigen
	${GTEST_LIBRARIES}
	)
