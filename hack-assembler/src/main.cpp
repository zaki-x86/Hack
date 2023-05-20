#include <stdio.h>
#include <string>
#include <sstream>


int main(int argc, const char** argv) {
    (void)argc;
    (void)argv;
    printf("Assembler is running!\n");    
    
    std::string input = "D=D+A;JMP";
    std::istringstream ss(input);
    std::string token;
    
    while(std::getline(ss, token, ';')) {
        printf("%s\n", token.c_str());
    }

    return 0;
}