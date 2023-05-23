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
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "parser.h"

TEST_CASE("Constructor test") {
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

TEST_CASE("Looping through commands test") {
    std::stringstream ss;
    ss << "D=M" << std::endl;
    ss << "D;JGT" << std::endl;
    ss << "D=D-M" << std::endl;
    ss << "M=D" << std::endl;
    ss << "(LOOP)" << std::endl;
    ss << "D=D-M" << std::endl;
    ss << "M=D" << std::endl;
    ss << "0;JMP" << std::endl;
    ss << "(END)" << std::endl;
    ss << "0;JMP" << std::endl;
    
    std::string filename = "test.asm";
    std::ofstream outfile(filename);
    outfile << ss.str();
    outfile.close();

    hack::assembler::parser parser(filename);

    CHECK(parser.more_commands());

    while (parser.more_commands())
    {
        parser.advance();

        if (!parser.more_commands())
        {
            CHECK(parser.more_commands() == false);
        }
    }
}

TEST_CASE("Parsing symbols from A-instructions and L-instructions test") {
    std::stringstream ss;
    ss << "@700" << std::endl;
    ss << "(LOOP)" << std::endl;
    
    std::string filename = "test.asm";
    std::ofstream outfile(filename);
    outfile << ss.str();
    outfile.close();

    hack::assembler::parser parser(filename);
    
    CHECK(parser.more_commands());

    while (parser.more_commands())
    {

        if (parser.command() == hack::assembler::command_type::A_COMMAND)
        {
            CHECK(parser.symbol() == "700");
        }
        else if (parser.command() == hack::assembler::command_type::L_COMMAND)
        {
            CHECK(parser.symbol() == "LOOP");
        }
        
        parser.advance();
    }
}

TEST_CASE("Parsing C-instructions test") {
    std::stringstream ss;
    ss << "D=M" << std::endl;
    ss << "D;JGT" << std::endl;
    ss << "D=D-M" << std::endl;
    ss << "M=D" << std::endl;
    ss << "(LOOP)" << std::endl;
    ss << "D-M" << std::endl;
    ss << "M=D" << std::endl;
    ss << "0;JMP" << std::endl;
    ss << "(END)" << std::endl;
    ss << "0;JMP" << std::endl;
    
    // construct a vector of tuples of the form (dest, comp, jump)
    std::vector<std::tuple<std::string, std::string, std::string>> expected = {
        {"D", "M", ""},
        {"", "D", "JGT"},
        {"D", "D-M", ""},
        {"M", "D", ""},
        {"", "", ""},
        {"", "D-M", ""},
        {"M", "D", ""},
        {"", "0", "JMP"},
        {"", "", ""},
        {"", "0", "JMP"}
    };

    std::string filename = "test.asm";
    std::ofstream outfile(filename);
    outfile << ss.str();
    outfile.close();

    hack::assembler::parser parser(filename);

    CHECK(parser.more_commands());

    while (parser.more_commands())
    {

        if (parser.command() == hack::assembler::command_type::C_COMMAND)
        {
            CHECK_MESSAGE(parser.dest() == std::get<0>(expected[parser.line_number() - 1]), "Command: " << parser.current_command());
            CHECK_MESSAGE(parser.comp() == std::get<1>(expected[parser.line_number() - 1]), "Command: " << parser.current_command());
            CHECK_MESSAGE(parser.jump() == std::get<2>(expected[parser.line_number() - 1]), "Command: " << parser.current_command());
        }
        
        parser.advance();
    }
}