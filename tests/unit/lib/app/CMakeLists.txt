
target_sources(pharaoh-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/ControlsTest.cc
	)

target_include_directories(pharaoh-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
