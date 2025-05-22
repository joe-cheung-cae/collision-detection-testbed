# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

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
set(CDT_VERSION_MAJOR 0 CACHE STRING "Major version of CDT" FORCE)
set(CDT_VERSION_MINOR 0 CACHE STRING "Minor version of CDT" FORCE)
set(CDT_VERSION_PATCH 1 CACHE STRING "Patch version of CDT" FORCE)
set(CDT_VERSION ${CDT_VERSION_MAJOR}.${CDT_VERSION_MINOR}.${CDT_VERSION_PATCH})

# Building time information
string(TIMESTAMP CDT_BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")

include(git_config)
set(CDT_GIT_HASH "")
set(CDT_GIT_BRANCH "")
get_git_hash(CDT_GIT_HASH)
get_git_branch(CDT_GIT_BRANCH)

project(joe-CDT LANGUAGES CXX CUDA VERSION ${CDT_VERSION_MAJOR}.${CDT_VERSION_MINOR}.${CDT_VERSION_PATCH})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message(STATUS "Version information:")
message(STATUS "    String value:      ${CDT_VERSION}")
message(STATUS "    Build time:        ${CDT_BUILD_TIMESTAMP}")
message(STATUS "    Git SHA value:     ${CDT_GIT_HASH}")
message(STATUS "    Git branch:        ${CDT_GIT_BRANCH}")

# print the host information
message(STATUS "Platform information:")
message(STATUS "    We are on a ${CMAKE_HOST_SYSTEM_NAME} system")
message(STATUS "    The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "    Building for a ${CMAKE_SYSTEM_NAME} system")
message(STATUS "    The target processor is ${CMAKE_SYSTEM_PROCESSOR}")

# ==================================================================================
# Options for building
# ==================================================================================
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build.")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release)

# Print the build type
message(STATUS "Build information:")
message(STATUS "    Build type is ${CMAKE_BUILD_TYPE}")
message(STATUS "    CMAKE_CUDA_ARCHITECTURES is ${CMAKE_CUDA_ARCHITECTURES}")

# Set the flags
set(CDT_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CDT_NVCC_FLAGS "${CUDA_NVCC_FLAGS}")
set(CDT_LINKERFLAG_EXE "${CMAKE_EXE_LINKER_FLAGS}")
set(CDT_LINKERFLAG_LIB "")

# ==================================================================================
# CXX standard configuration
# ==================================================================================
set(CDT_CXX_STD 17 CACHE STRING "Choose the C++ standard for project building.")
set_property(CACHE CDT_CXX_STD PROPERTY STRINGS 14 17 20)

# ==================================================================================
# CUDA Package configuration
# ==================================================================================
message(STATUS "Finding CUDA toolkit...")
find_package(CUDAToolkit REQUIRED)

# Global fix for CUDA language bug
include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

# Print the CUDA toolkit information
message(STATUS "    CUDA Compiler Version:                  ${CMAKE_CUDA_COMPILER_VERSION}")
message(STATUS "    CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES: ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}")