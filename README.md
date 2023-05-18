# Hack Machine

This project is part of [Nand2tetris course](https://www.coursera.org/learn/nand2tetris2).

## Introduction

The Hack Machine is a simple computer with a CPU, two separate memories (ROM and RAM), and two memory-mapped I/O devices (screen and keyboard). The machine language of the Hack Machine consists of two types of instructions only: A-instructions and C-instructions. The Hack Machine is designed to execute programs written in the Hack assembly language, and hack high-level language programs that have been compiled to the Hack VM language.

## Specification

### [The Hack Machine](docs/HackMachineSpecs.md)

The Hack Machine is a von Neumann architecture machine. It consists of a CPU, two separate memories (ROM and RAM), and two memory-mapped I/O devices (screen and keyboard). The machine language of the Hack Machine consists of two types of instructions only: A-instructions and C-instructions. The Hack Machine is designed to execute programs written in the Hack assembly language, and hack high-level language programs that have been compiled to the Hack VM language.

Read more:

- [Hack Machine Specification](docs/HackMachineSpecs.md)
- [Hack Machine Language](docs/HackMachineLanguage.md)

### [Hack Assembler](docs/HackAssembler.md)

The Hack Assembler is a program that translates programs written in the Hack assembly language into the Hack machine language.

Assemblers translates symbolic assembly code to binary code. Without symbols or labels, the assember is just a dumb text processing program. It is the symbols and labels that give the assembler its power.

The programmer can use symbolic variable names, and the translator will automatically assign them to memory addresses. The programmer can also use symbolic labels to mark locations in the program, and the translator will replace them with the appropriate ROM addresses, either conditionally or unconditionally.

The assembler receives a stream of commands, and carries out of the following tasks (not necessarily in this order):

1. Eliminate all white space and comments.
2. Parse each line into its underlying fields.
3. Translate each symbolic A-instruction into its equivalent binary value.
4. Translate each C-instruction into its equivalent binary value.
5. Assign ROM addresses to each instruction, starting at 0.
6. Assign RAM addresses to each variable, starting at 16.

Read more:

- [The Hack Assembler](docs/HackAssembler.md)

### [Hack Virtual Machine](docs/HackVirtualMachine.md)

Read more:

- [The Hack Virtual Machine](docs/HackVirtualMachine.md)

### [Hack Compiler](docs/HackCompiler.md)

Read more:

- [The Hack Compiler](docs/HackCompiler.md)