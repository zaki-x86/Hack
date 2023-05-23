/**
 * @file common.h
 * @author M Zaki (zaki.x86@gmail.com)
 * @brief Common header includes utility functions and classes
 * @version 0.1
 * @date 2023-08-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _COMMON_H_

#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

namespace hack::assembler {

    enum class command_type
    {
        A_COMMAND,
        C_COMMAND,
        L_COMMAND
    };

    
}

#endif // !_COMMON_H_