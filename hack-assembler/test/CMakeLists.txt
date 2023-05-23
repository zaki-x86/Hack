
file(GLOB_RECURSE TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

foreach(file ${TEST_SRCS})
    message(STATUS "Adding test ${file}")
    get_filename_component(TEST_NAME ${file} NAME_WE)
    add_executable(${TEST_NAME} ${file})

    target_include_directories(
        ${TEST_NAME}
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/../common
    )

    target_link_libraries(
        ${TEST_NAME}
        PUBLIC
        HackAssembler_lib
    )
    
    doctest_add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} --no-skipped-summary --no-version -ltc)

endforeach()

