#include "parser.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

using namespace hack::assembler;

parser::parser(std::string filename) 
    :   m_commands(), 
        m_currentCommand(m_commands.begin())
{
    // Check if input file is a .asm file
    if (filename.substr(filename.find_last_of(".") + 1) != "asm")
    {
        throw std::invalid_argument("Input file must be a .asm file");
    }

    // Open input file
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        throw std::invalid_argument("Input file could not be opened");
    }

    // Read input file into a vector of strings
    std::string line;
    while (std::getline(inputFile, line))
    {
        // Remove comments
        line = line.substr(0, line.find("//"));

        // Remove whitespace
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        // Skip empty lines
        if (line.empty())
        {
            continue;
        }

        // Add line to vector
        m_commands.push_back(line);
    }

    // Close input file
    inputFile.close();

    // Set current command to first command
    m_currentCommand = m_commands.begin();
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
    // Check if current command is an A_COMMAND
    if (m_currentCommand->front() == '@')
    {
        return command_type::A_COMMAND;
    }

    // Check if current command is an L_COMMAND
    else if (m_currentCommand->front() == '(') 
    {
        return command_type::L_COMMAND;
    }

    // Current command is a C_COMMAND
    else
    {
        return command_type::C_COMMAND;
    }
}

std::string parser::symbol() const
{
    if (command() == command_type::A_COMMAND)
    {
        return m_currentCommand->substr(1);
    }
    else if (command() == command_type::L_COMMAND)
    {
        return m_currentCommand->substr(1, m_currentCommand->size() - 2);
    }
    else
    {
        throw std::invalid_argument("Current command is not an A_COMMAND or L_COMMAND");
    }
}

std::string parser::dest() const
{
    if (command() == command_type::C_COMMAND)
    {
        return m_currentCommand->substr(0, m_currentCommand->find('='));
    }
    else
    {
        throw std::invalid_argument("Current command is not a C_COMMAND");
    }
}

std::string parser::comp() const
{
    if (command() == command_type::C_COMMAND)
    {
        return m_currentCommand->substr(m_currentCommand->find('=') + 1, m_currentCommand->find(';') - m_currentCommand->find('=') - 1);
    }
    else
    {
        throw std::invalid_argument("Current command is not a C_COMMAND");
    }
}

std::string parser::jump() const
{
    if (command() == command_type::C_COMMAND)
    {
        return m_currentCommand->substr(m_currentCommand->find(';') + 1);
    }
    else
    {
        throw std::invalid_argument("Current command is not a C_COMMAND");
    }
}


