#include <stdio.h>
#include <string>
#include <sstream>

#include "hack_assembler.h"


int main(int argc, const char** argv) {
    (void)argc;
    (void)argv;
    printf("Assembler is running!\n");

    // check if a '.asm' file is supplied as program argument
    if (argc < 2)
    {
        //throw std::runtime_error("No input file supplied");
        printf("No input file supplied\n");
    }

    //std::string filename = argv[1];
    
    //hack::assembler::parser p(filename);
    hack::assembler::coder c;
    hack::assembler::sym_table st;

    return 0;
}
