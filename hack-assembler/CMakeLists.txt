project(
    "HackAssembler"
)

message(STATUS "Building ${PROJECT_NAME} ...")

file(GLOB_RECURSE ASSEMBLER_SOURCES "src/*.cpp")
file(GLOB_RECURSE ASSEMBLER_HEADERS "src/*.h")
add_executable(HackAssembler ${ASSEMBLER_SOURCES})
target_compile_features(HackAssembler PUBLIC cxx_std_17)

# Copy _builtin directory to build directory
message(STATUS "Copying symbol tables to build directory ...")
add_custom_command(TARGET HackAssembler POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/_builtin $<TARGET_FILE_DIR:${PROJECT_NAME}>/_builtin
)

target_link_libraries(HackAssembler INTERFACE CSVParser)

# # set include directories:
# target_include_directories(HackAssembler
#     PUBLIC
#     ${CMAKE_SOURCE_DIR}/common/csv
# )

# check directories that are linked to the target:
get_target_property(_target_include_dirs HackAssembler INCLUDE_DIRECTORIES)
message(STATUS "Include directories of ${PROJECT_NAME}: ${_target_include_dirs}")

message(STATUS "Building ${PROJECT_NAME} done!")

message(STATUS "Building ${PROJECT_NAME} tests ...")
add_library(HackAssembler_lib STATIC ${ASSEMBLER_SOURCES} ${ASSEMBLER_HEADERS})
add_subdirectory(test)
