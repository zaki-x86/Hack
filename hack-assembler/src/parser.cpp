#include "parser.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

using namespace hack::assembler;

parser::parser(const char* filename) 
    : m_commands(), m_currentCommand(m_commands.begin())
{

}

parser::~parser()
{

}

bool parser::more_commands() const
{
    return m_currentCommand != m_commands.end();
}

void parser::advance()
{
    ++m_currentCommand;
}

command_type parser::command() const
{
    return command_type::A_COMMAND;
}

std::string parser::symbol() const
{
    return "";
}

std::string parser::dest() const
{
    return "";
}

std::string parser::comp() const
{
    return "";
}

std::string parser::jump() const
{
    return "";
}


