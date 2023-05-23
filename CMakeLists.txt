cmake_minimum_required(VERSION 3.24)

project(
    "HackStack"
    VERSION 0.1.0
    DESCRIPTION "Hack assembler, virtual machine, and compiler"
    LANGUAGES CXX
)

set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
    message(STATUS "XSTL is being built as a main project")
endif()

##################################
# Setup Scripts directory
##################################
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake ${CMAKE_MODULE_PATH})
message(STATUS "Module path is set to: ${CMAKE_MODULE_PATH}")
#include(Utils)
#include(CompilerWarnings)
include(common)
##################################
# Build options
##################################

# Prevent building in source dir
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.\n")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Started CMake for ${XSTL_TARGET} v${PROJECT_VERSION}...\n")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    if (UNIX OR MINGW OR CMAKE_COMPILER_IS_GNUCXX )    
        add_compile_options("$<$<CONFIG:DEBUG>:-D_DEBUG>")    #this will allow to use same _DEBUG macro available in both Linux as well as Windows - MSCV environment. Easy to put Debug specific code.
    endif ()
    message(STATUS "_DEBUG macro is added for debugging specific code\n")
endif()

message(STATUS "Building hack ...")
add_subdirectory(hack-assembler)
add_subdirectory(hack-vm)
add_subdirectory(hack-compiler)