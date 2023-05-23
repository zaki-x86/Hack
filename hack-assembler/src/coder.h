/**
 * @file coder.h
 * @author M Zaki (zaki.x86@gmail.com)
 * @brief Coder class
 * @version 0.1
 * @date 2023-08-28
 * 
 */

#ifndef _ASSEMBLER_CODER_H_
#define _ASSEMBLER_CODER_H_

#include <map>
#include <string>
#include <bitset>

namespace hack::assembler {
    class coder {
    public:
        coder();
        ~coder() = default;
        coder(const coder&) = delete;
        coder(coder&&) = delete;
        coder& operator=(const coder&) = delete;
        coder& operator=(coder&&) = delete;
        
        std::bitset<3> dest(const std::string& mnemonic) const;
        std::bitset<7> comp(const std::string& mnemonic) const;
        std::bitset<3> jump(const std::string& mnemonic) const;

    private:
        std::map<std::string, std::bitset<3>> m_dest;
        std::map<std::string, std::bitset<7>> m_comp;
        std::map<std::string, std::bitset<3>> m_jump;
    };
}

#endif // !_ASSEMBLER_CODER_H_