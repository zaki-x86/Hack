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

#include "csv.h"
#include "coder.h"

TEST_CASE("Coder can convert any dest symbol into equivalent opcode") {
    // Initialize symbol table, symbols are located in `_builtin/hack-dest`
    // pass symbols to coder::dest() to output equivalent 3 bit opecode

    hack::assembler::coder c;
    std::string mnemonic;
    std::bitset<3> opcode;

    SUBCASE("Mnemonic: null") {
        mnemonic = "null";
        opcode = c.dest(mnemonic);
        CHECK_MESSAGE(opcode == std::bitset<3>("000"), "null should return 000, got " << opcode.to_string() + " instead");
    }

    SUBCASE("Mnemonic: M") {
        mnemonic = "M";
        opcode = c.dest(mnemonic);
        CHECK(opcode == std::bitset<3>("001"));
    }

    SUBCASE("Mnemonic: D") {
        mnemonic = "D";
        opcode = c.dest(mnemonic);
        CHECK(opcode == std::bitset<3>("010"));
    }

    SUBCASE("Mnemonic: MD") {
        mnemonic = "MD";
        opcode = c.dest(mnemonic);
        CHECK(opcode == std::bitset<3>("011"));
    }

    SUBCASE("Mnemonic: A") {
        mnemonic = "A";
        opcode = c.dest(mnemonic);
        CHECK(opcode == std::bitset<3>("100"));
    }

    SUBCASE("Mnemonic: AM") {
        mnemonic = "AM";
        opcode = c.dest(mnemonic);
        CHECK(opcode == std::bitset<3>("101"));
    }

    SUBCASE("Mnemonic: AD") {
        mnemonic = "AD";
        opcode = c.dest(mnemonic);
        CHECK(opcode == std::bitset<3>("110"));
    }

    SUBCASE("Mnemonic: AMD") {
        mnemonic = "AMD";
        opcode = c.dest(mnemonic);
        CHECK(opcode == std::bitset<3>("111"));
    }
}

TEST_CASE("Coder can convert any comp symbol into equivalent opcode") {
    // Initialize symbol table, symbols are located in `_builtin/hack-comp`
    // pass symbols to coder::comp() to output equivalent 7 bit opecode

    hack::assembler::coder c;
    std::string mnemonic;
    std::bitset<7> opcode;
    
    SUBCASE("Mnemonic: 0") {
        mnemonic = "0";
        opcode = c.comp(mnemonic);
        CHECK(opcode == std::bitset<7>("0101010"));
    }
    
    SUBCASE("Mnemonic: 1") {
        mnemonic = "1";
        opcode = c.comp(mnemonic);
        CHECK(opcode == std::bitset<7>("0111111"));
    }

    SUBCASE("Mnemonic: -1") {
        mnemonic = "-1";
        opcode = c.comp(mnemonic);
        CHECK(opcode == std::bitset<7>("0111010"));
    }

    SUBCASE("Mnemonic: D") {
        mnemonic = "D";
        opcode = c.comp(mnemonic);
        CHECK(opcode == std::bitset<7>("0001100"));
    }

    SUBCASE("Mnemonic: A") {
        mnemonic = "A";
        opcode = c.comp(mnemonic);
        CHECK(opcode == std::bitset<7>("0110000"));
    }

    SUBCASE("Mnemonic: !D") {
        mnemonic = "!D";
        opcode = c.comp(mnemonic);
        CHECK(opcode == std::bitset<7>("0001101"));
    }

    SUBCASE("Mnemonic: !A") {
        mnemonic = "!A";
        opcode = c.comp(mnemonic);
        CHECK(opcode == std::bitset<7>("0110001"));
    }

    SUBCASE("Mnemonic: -D") {
        mnemonic = "-D";
        opcode = c.comp(mnemonic);
        CHECK(opcode == std::bitset<7>("0001111"));
    }

    // Rest of the symbols needs to be verified but that's too boring
}

TEST_CASE("Coder can convert any jump symbol into equivalent opcode") {
    // Initialize symbol table, symbols are located in `_builtin/hack-jump`
    // pass symbols to coder::jump() to output equivalent 3 bit opecode

    hack::assembler::coder c;
    std::string mnemonic;
    std::bitset<3> opcode;

    SUBCASE("Mnemonic: null") {
        mnemonic = "null";
        opcode = c.jump(mnemonic);
        CHECK_MESSAGE(opcode == std::bitset<3>("000"), "null should return 000, got " << opcode.to_string() + " instead");
    }

    SUBCASE("Mnemonic: JGT") {
        mnemonic = "JGT";
        opcode = c.jump(mnemonic);
        CHECK(opcode == std::bitset<3>("001"));
    }

    SUBCASE("Mnemonic: JEQ") {
        mnemonic = "JEQ";
        opcode = c.jump(mnemonic);
        CHECK(opcode == std::bitset<3>("010"));
    }

    SUBCASE("Mnemonic: JGE") {
        mnemonic = "JGE";
        opcode = c.jump(mnemonic);
        CHECK(opcode == std::bitset<3>("011"));
    }

    SUBCASE("Mnemonic: JLT") {
        mnemonic = "JLT";
        opcode = c.jump(mnemonic);
        CHECK(opcode == std::bitset<3>("100"));
    }

    SUBCASE("Mnemonic: JNE") {
        mnemonic = "JNE";
        opcode = c.jump(mnemonic);
        CHECK(opcode == std::bitset<3>("101"));
    }

    SUBCASE("Mnemonic: JLE") {
        mnemonic = "JLE";
        opcode = c.jump(mnemonic);
        CHECK(opcode == std::bitset<3>("110"));
    }

    SUBCASE("Mnemonic: JMP") {
        mnemonic = "JMP";
        opcode = c.jump(mnemonic);
        CHECK(opcode == std::bitset<3>("111"));
    }
}