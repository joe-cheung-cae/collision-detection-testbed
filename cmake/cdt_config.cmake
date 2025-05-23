configure_file(
    "${CMAKE_SOURCE_DIR}/src/cdt_core/cdt_config.hpp.in"
    "${CMAKE_BINARY_DIR}/src/cdt_core/cdt_config.hpp"
    @ONLY
)

include_directories(
    "${CMAKE_BINARY_DIR}/src/cdt_core"
)