#ifndef _ASSEM_SYM_TABLE_H_
#define _ASSEM_SYM_TABLE_H_

#include <string>
#include <map>

namespace hack::assembler
{
    class sym_table
    {
    public:
        using address_t = unsigned int;
    public:
        sym_table();
        ~sym_table();

        void push(const std::pair<std::string, address_t>& p);
        void push(std::pair<std::string, address_t>&& p);

        bool contains(const std::string& key) const;
        bool contains(std::string&& key) const;

        address_t address(const std::string& key) const;
        address_t address(std::string&& key) const;

    private:
        std::map<std::string, address_t> m_table;
    };

} // namespace hack::assembler


#endif // !_ASSEM_SYM_TABLE_H_