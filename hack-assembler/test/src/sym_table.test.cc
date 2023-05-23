#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <iostream>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <bitset>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "sym_table.h"

TEST_CASE("sym_table is initialized correctly with all predefined symbols") {
    hack::assembler::sym_table table;

    CHECK_MESSAGE((table.contains("SP") && table.address("SP") == 0), "SP is not defined");
    CHECK_MESSAGE((table.contains("LCL") && table.address("LCL") == 1), "LCL is not defined");
    CHECK_MESSAGE((table.contains("ARG") && table.address("ARG") == 2), "ARG is not defined");
    CHECK_MESSAGE((table.contains("THIS") && table.address("THIS") == 3), "THIS is not defined");
    CHECK_MESSAGE((table.contains("THAT") && table.address("THAT") == 4), "THAT is not defined");
    CHECK_MESSAGE((table.contains("R0") && table.address("R0") == 0), "R0 is not defined");
    CHECK_MESSAGE((table.contains("R1") && table.address("R1") == 1), "R1 is not defined");
    CHECK_MESSAGE((table.contains("R2") && table.address("R2") == 2), "R2 is not defined");
    CHECK_MESSAGE((table.contains("R3") && table.address("R3") == 3), "R3 is not defined");
    CHECK_MESSAGE((table.contains("R4") && table.address("R4") == 4), "R4 is not defined");
    CHECK_MESSAGE((table.contains("R5") && table.address("R5") == 5), "R5 is not defined");
    CHECK_MESSAGE((table.contains("R6") && table.address("R6") == 6), "R6 is not defined");
    CHECK_MESSAGE((table.contains("R7") && table.address("R7") == 7), "R7 is not defined");
    CHECK_MESSAGE((table.contains("R8") && table.address("R8") == 8), "R8 is not defined");
    CHECK_MESSAGE((table.contains("R9") && table.address("R9") == 9), "R9 is not defined");
    CHECK_MESSAGE((table.contains("R10") && table.address("R10") == 10), "R10 is not defined");
    CHECK_MESSAGE((table.contains("R11") && table.address("R11") == 11), "R11 is not defined");
    CHECK_MESSAGE((table.contains("R12") && table.address("R12") == 12), "R12 is not defined");
    CHECK_MESSAGE((table.contains("R13") && table.address("R13") == 13), "R13 is not defined");
    CHECK_MESSAGE((table.contains("R14") && table.address("R14") == 14), "R14 is not defined");
    CHECK_MESSAGE((table.contains("R15") && table.address("R15") == 15), "R15 is not defined");
    CHECK_MESSAGE((table.contains("SCREEN") && table.address("SCREEN") == 16384), "SCREEN is not defined");
    CHECK_MESSAGE((table.contains("KBD") && table.address("KBD") == 24576), "KBD is not defined");
}

TEST_CASE("sym_table can accept symbols and return their addresses") {
    hack::assembler::sym_table table;

    table.push({"FOO", 100});
    table.push({"BAR", 111});
    CHECK_MESSAGE((table.contains("FOO") && table.address("FOO") == 100), "FOO is not defined");
    CHECK_MESSAGE((table.contains("BAR") && table.address("BAR") == 111), "BAR is not defined");

    CHECK_THROWS_AS(table.push({"KOO", 65536}), std::runtime_error);
    
}