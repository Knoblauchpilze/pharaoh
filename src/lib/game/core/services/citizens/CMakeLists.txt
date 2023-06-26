
target_include_directories (pharaoh_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/astar
	)

target_sources (pharaoh_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/LocatorAdaptor.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Runner.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Immigrant.cc
	)
