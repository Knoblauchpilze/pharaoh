
target_sources (pharaoh_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Coordinate.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Calendar.cc
	${CMAKE_CURRENT_SOURCE_DIR}/TimeManager.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Terrain.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Building.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Tile.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Map.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Scenario.cc
	)

target_include_directories (pharaoh_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
