#include <stdio.h>
#include <string>
#include <sstream>

#include "parser.h"
#include "coder.h"
#include "sym_table.h"

int main(int argc, const char** argv) {
    (void)argc;
    (void)argv;
    printf("Assembler is running!\n");    
    
    //hack::assembler::parser p;
    hack::assembler::coder c;
    hack::assembler::sym_table st;

    return 0;
}
