
add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/core
	)

target_sources (pharaoh_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Game.cc
	${CMAKE_CURRENT_SOURCE_DIR}/SavedGames.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GameState.cc
	)

target_include_directories (pharaoh_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
