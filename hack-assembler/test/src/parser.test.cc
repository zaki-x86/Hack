#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <iostream>
#include <cstdint>
#include <sstream>
#include <fstream>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "parser.h"

TEST_CASE("Constructor throws exception when initialized with bad file name") {
    std::stringstream ss;
    ss << "D=M" << std::endl;
    // ss << "D;JGT" << std::endl;
    // ss << "D=D-M" << std::endl;
    // ss << "M=D" << std::endl;
    // ss << "(LOOP)" << std::endl;
    // ss << "D=D-M" << std::endl;
    // ss << "M=D" << std::endl;
    // ss << "0;JMP" << std::endl;
    // ss << "(END)" << std::endl;
    // ss << "0;JMP" << std::endl;
    
    std::string filename = "test.asm";
    std::ofstream outfile(filename);
    outfile << ss.str();
    outfile.close();

    std::string bad_filename = "test";
    std::ofstream bad_outfile(bad_filename);
    bad_outfile << ss.str();
    bad_outfile.close();

    INFO("Good file name: " << filename);
    hack::assembler::parser parser(filename);
    try
    {
        INFO("Bad file name: " << bad_filename << " (should throw exception)");
        hack::assembler::parser bad_parser(bad_filename);
    }
    catch (const std::exception&)
    {
        CHECK(true);
    }
}