#ifndef _HACK_ASSEMBLER_H_
#define _HACK_ASSEMBLER_H_

#include "parser.h"
#include "coder.h"
#include "sym_table.h"

namespace hack
{
    class hack_assembler
    {
    public:
        hack_assembler(std::string filename);
        hack_assembler(hack_assembler &&) = delete;
        hack_assembler(const hack_assembler &) = delete;
        hack_assembler &operator=(hack_assembler &&) = delete;
        hack_assembler &operator=(const hack_assembler &) = delete;
        ~hack_assembler() = default;

        bool run();
    
    private:
        std::string m_filename;
        assembler::parser m_parser;
        assembler::coder m_coder;
        assembler::sym_table m_symTable;
    };
    
} // namespace hack


#endif // !_HACK_ASSEMBLER_H_