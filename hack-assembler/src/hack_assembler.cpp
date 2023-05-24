#include "hack_assembler.h"

hack::hack_assembler::hack_assembler(std::string filename)
    : m_filename(filename),
      m_parser(filename),
      m_coder(),
      m_symTable()
{
}

bool hack::hack_assembler::run()
{
    return false;
}
