#ifndef _ASSMBLY_PARSER_H_

#include <vector>
#include <string>

#include "common.h"

namespace hack::assembler
{
    class parser
    {
    public:
        parser(std::string filename);
        ~parser();
        parser(parser &&) = delete;
        parser(const parser &) = delete;
        parser &operator=(parser &&) = delete;
        parser &operator=(const parser &) = delete;

        bool more_commands() const;
        void advance(); 
        command_type command() const;
        std::string current_command() const;
        std::string symbol() const;
        std::string dest() const;
        std::string comp() const;
        std::string jump() const;
        size_t line_number() const;
        inline size_t size() const;

    private:
        std::vector<std::string> m_commands;
        std::vector<std::string>::iterator m_currentCommand;
    };
}

#endif // !_ASSMBLY_PARSER_H_