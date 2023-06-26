
target_sources (pharaoh_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Node.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Path.cc
	${CMAKE_CURRENT_SOURCE_DIR}/AStarNodes.cc
	${CMAKE_CURRENT_SOURCE_DIR}/AStar.cc
	)

	target_include_directories (pharaoh_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
