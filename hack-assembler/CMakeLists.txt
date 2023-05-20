cmake_minimum_required(VERSION 3.24)

project(
    "HackAssembler"
    VERSION 0.1.0
    DESCRIPTION "Hack assembler written in C++"
    LANGUAGES CXX
)

set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
    message(STATUS "${PROJECT_NAME} is being built as a main project")
    set(CMAKE_MODULE_PATH ../scripts/cmake ${CMAKE_MODULE_PATH})
    message(STATUS "Module path is set to: ${CMAKE_MODULE_PATH}")
    #include(Utils)
    #include(CompilerWarnings)
    include(common)
else()
    message(STATUS "${PROJECT_NAME} is being built as a sub-project of ${CMAKE_PROJECT_NAME}")
endif()

file(GLOB_RECURSE ASSEMBLER_SOURCES "src/*.cpp")
file(GLOB_RECURSE ASSEMBLER_HEADERS "src/*.h")

message(STATUS "Building ${PROJECT_NAME} ...")
add_executable(${PROJECT_NAME} ${ASSEMBLER_SOURCES} ${ASSEMBLER_HEADERS})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

message(STATUS "Building ${PROJECT_NAME} done!")

message(STATUS "Building ${PROJECT_NAME} tests ...")
add_library(${PROJECT_NAME}_lib STATIC ${ASSEMBLER_SOURCES} ${ASSEMBLER_HEADERS})
add_subdirectory(test)