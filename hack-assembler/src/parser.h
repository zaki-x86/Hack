#ifndef _ASSMBLY_PARSER_H_

#include <vector>
#include <string>

namespace hack::assembler
{
    enum class command_type
    {
        A_COMMAND,
        C_COMMAND,
        L_COMMAND
    };

    class parser
    {
    public:
        parser(const char* filename);
        ~parser();
        parser(parser &&) = delete;
        parser(const parser &) = delete;
        parser &operator=(parser &&) = delete;
        parser &operator=(const parser &) = delete;

        bool more_commands() const;
        void advance(); 
        command_type command() const;
        std::string symbol() const;
        std::string dest() const;
        std::string comp() const;
        std::string jump() const;
    };

    private:
        std::vector<std::string> m_commands;
        std::vector<std::string>::iterator m_currentCommand;
    };
}

#endif // !_ASSMBLY_PARSER_H_