#include "sym_table.h"

#include "csv.h"
#include <filesystem>

using namespace hack::assembler;

sym_table::sym_table()
    : m_table()
{
    std::string predefined_symbols_file = std::filesystem::current_path().append("_builtin\\hack-predefined.s").string();
    io::CSVReader<2> in(predefined_symbols_file);
    in.read_header(io::ignore_extra_column, "label", "address");
    std::string label;
    address_t address;

    while (in.read_row(label, address)) {
        m_table.insert({ label, address });
    }
}

sym_table::~sym_table()
{}

void hack::assembler::sym_table::push(const std::pair<std::string, address_t> &p)
{
    if (p.second > 32767)
    {
        throw std::runtime_error("Address out of range");
    }

    m_table.insert(p);
    
}

void hack::assembler::sym_table::push(std::pair<std::string, address_t> &&p)
{
    if (p.second > 32767)
    {
        throw std::runtime_error("Address out of range");
    }

    m_table.insert(p);
}

bool hack::assembler::sym_table::contains(const std::string &key) const
{
    return m_table.find(key) != m_table.end();
}

bool hack::assembler::sym_table::contains(std::string &&key) const
{
    return m_table.find(key) != m_table.end();
}

sym_table::address_t hack::assembler::sym_table::address(const std::string &key) const
{
    return m_table.at(key);
}

sym_table::address_t hack::assembler::sym_table::address(std::string &&key) const
{
    return m_table.at(key);
}