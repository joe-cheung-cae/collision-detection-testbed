# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

project(CGAT VERSION 0.1.0 LANGUAGES CXX CUDA)

# Prevent in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are not allowed. Please create a separate build directory.")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

# Set the cmake config directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Set the cuda architecture
set(CUDA_ARCH native CACHE STRING "Choose the target architecture of cuda.")
set_property(CACHE CUDA_ARCH PROPERTY STRINGS all native all-major manual)

# Set the CMAKE_CUDA_ARCHITECTURES when configure cmake
if(NOT CUDA_ARCH STREQUAL "manual")
    set(CMAKE_CUDA_ARCHITECTURES ${CUDA_ARCH})
    mark_as_advanced(FORCE CMAKE_CUDA_ARCHITECTURES)
else()
    mark_as_advanced(CLEAR CMAKE_CUDA_ARCHITECTURES)
    set(CMAKE_CUDA_ARCHITECTURES 52)
endif()

# String version information
set(TriTriIns_VERSION_MAJOR 0 CACHE STRING "Major version of TriTriIns" FORCE)
set(TriTriIns_VERSION_MINOR 0 CACHE STRING "Minor version of TriTriIns" FORCE)
set(TriTriIns_VERSION_PATCH 1 CACHE STRING "Patch version of TriTriIns" FORCE)
set(TriTriIns_VERSION ${TriTriIns_VERSION_MAJOR}.${TriTriIns_VERSION_MINOR}.${TriTriIns_VERSION_PATCH})

# Building time information
string(TIMESTAMP TriTriIns_BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")

include(git_config)
set(TriTriIns_GIT_HASH "")
set(TriTriIns_GIT_BRANCH "")
get_git_hash(TriTriIns_GIT_HASH)
get_git_branch(TriTriIns_GIT_BRANCH)

project(joe-engine LANGUAGES CXX CUDA VERSION ${TriTriIns_VERSION_MAJOR}.${TriTriIns_VERSION_MINOR}.${TriTriIns_VERSION_PATCH})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message(STATUS "Version information:")
message(STATUS "    String value:      ${TriTriIns_VERSION}")
message(STATUS "    Build time:        ${TriTriIns_BUILD_TIMESTAMP}")
message(STATUS "    Git SHA value:     ${TriTriIns_GIT_HASH}")
message(STATUS "    Git branch:        ${TriTriIns_GIT_BRANCH}")

# print the host information
message(STATUS "Platform information:")
message(STATUS "    We are on a ${CMAKE_HOST_SYSTEM_NAME} system")
message(STATUS "    The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "    Building for a ${CMAKE_SYSTEM_NAME} system")
message(STATUS "    The target processor is ${CMAKE_SYSTEM_PROCESSOR}")