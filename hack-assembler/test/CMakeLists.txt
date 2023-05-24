file(GLOB_RECURSE TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
enable_testing()
include(CTest)

foreach(file ${TEST_SRCS})
    message(STATUS "Adding test ${file}")
    get_filename_component(TEST_NAME ${file} NAME_WE)
    add_executable(${TEST_NAME} ${file})

    target_include_directories(
        ${TEST_NAME}
        PUBLIC
        ${CMAKE_SOURCE_DIR}/hack-assembler/src
        ${CMAKE_SOURCE_DIR}/common
    )

    target_link_libraries(
        ${TEST_NAME}
        PUBLIC
        HackAssembler_lib
    )

    doctest_add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} --no-skipped-summary --no-version -ltc)

endforeach()

# Copy directory _builtin/ from the main source directory to the binary directory
message(STATUS "Copying symbol tables to build directory ...")
add_custom_command(TARGET ${TEST_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/_builtin $<TARGET_FILE_DIR:${TEST_NAME}>/_builtin
)