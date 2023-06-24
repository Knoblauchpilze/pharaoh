
target_sources (pharaoh_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Service.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Migrants.cc
	)

target_include_directories (pharaoh_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
