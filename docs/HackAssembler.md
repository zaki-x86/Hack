# The Hack Assembler

The assembler will be implemented in two stages. In the first stage, we will write a program that translates assembly programs that contain no symbolic variables or labels. In the second stage, we will extend the program to handle variables and labels.

## Specification

### Syntax conventions and file formats

**File Names** By convention, programs in binary machine code and in assembly
code are stored in text files with **hack** and **asm** extensions, respectively. Thus, a
`Prog.asm` file is translated by the assembler into a `Prog.hack` file.

**Binary files (.hack)** is a file containing a sequence of 16-bit little-endian. The binary code in the n-th line of the file corresponds to the instruction stored in ROM address n.

**Assembly files (.asm)** is a text file containing a sequence of commands. Each command is written in a separate line. There are two types of commands: A-instructions and C-instructions. Comments can be added to the file using the `//` notation. The assembler ignores all white space characters and comments.

## Implementation

The assembler consists of 3 modules: `parser`, `coder`, and `sym_table`.

### Parser

The parser module is responsible for parsing each line of the assembly program into its underlying fields. It also removes all white space and comments.

The parser module is implemented as a class called `parser` in namespace `hack::assembler`. The constructor receives as an argument an input file path. The parser reads the input stream, parses each line, and provides convenient access to the fields and symbols contained in the line.

#### API

The parser class provides the following API:

```cpp
class parser {
public:
    parser(const std::string& file_path);
    bool more_commands() const;
    void advance();
    command_type command() const;
    std::string symbol() const;
    std::string dest() const;
    std::string comp() const;
    std::string jump() const;
};
```

The constructor receives as an argument the path to the input file. The constructor opens the input stream and reads the first line of the file. The constructor throws an exception if the file cannot be opened.