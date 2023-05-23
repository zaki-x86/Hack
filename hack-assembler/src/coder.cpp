#include "coder.h"

#include <iostream>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <bitset>
#include <filesystem>

#include "csv.h"

using namespace hack::assembler;

coder::coder()
    : m_dest(),
      m_comp(),
      m_jump() 
{
    // reads the symbol tables stored in `_builtin/hack-dest.s`, `_builtin/hack-comp.s`, `_builtin/hack-jump.s`
    // and stores them in `m_dest`, `m_comp`, `m_jump` respectively
    // get absolute path
    std::string dest_path = std::filesystem::current_path().append("_builtin\\hack-dest.s").string();
    std::string comp_path = std::filesystem::current_path().append("_builtin\\hack-comp.s").string();
    std::string jump_path = std::filesystem::current_path().append("_builtin\\hack-jump.s").string();

    io::CSVReader<2> dest_f(dest_path);
    dest_f.read_header(io::ignore_extra_column, "symbol", "opcode");
    io::CSVReader<2> comp_f(comp_path);
    comp_f.read_header(io::ignore_extra_column, "symbol", "opcode");
    io::CSVReader<2> jump_f(jump_path);
    jump_f.read_header(io::ignore_extra_column, "symbol", "opcode");

    std::string symbol;
    std::string opcode;
    while (dest_f.read_row(symbol, opcode)) {
        m_dest.insert({symbol, std::bitset<3>(opcode)});
    }
    while (comp_f.read_row(symbol, opcode)) {
        m_comp.insert({symbol, std::bitset<7>(opcode)});
    }
    while (jump_f.read_row(symbol, opcode)) {
        m_jump.insert({symbol, std::bitset<3>(opcode)});
    }

    if (m_dest.empty() || m_comp.empty() || m_jump.empty())
        throw std::runtime_error("Error reading symbol tables");   
}

std::bitset<3> coder::dest(const std::string& mnemonic) const {
    return m_dest.at(mnemonic);
}

std::bitset<7> coder::comp(const std::string& mnemonic) const {
    return m_comp.at(mnemonic);
}

std::bitset<3> coder::jump(const std::string& mnemonic) const {
    return m_jump.at(mnemonic);
}
