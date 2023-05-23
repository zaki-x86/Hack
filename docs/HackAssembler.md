# The Hack Assembler

The assembler will be implemented in two stages. In the first stage, we will write a program that translates assembly programs that contain no symbolic variables or labels. In the second stage, we will extend the program to handle variables and labels.

## Syntax conventions and file formats

**File Names** By convention, programs in binary machine code and in assembly
code are stored in text files with **hack** and **asm** extensions, respectively. Thus, a
`Prog.asm` file is translated by the assembler into a `Prog.hack` file.

**Binary files (.hack)** is a file containing a sequence of 16-bit little-endian. The binary code in the n-th line of the file corresponds to the instruction stored in ROM address n.

**Assembly files (.asm)** is a text file containing a sequence of commands. Each command is written in a separate line. There are two types of commands: A-instructions and C-instructions. Comments can be added to the file using the `//` notation. The assembler ignores all white space characters and comments.

## API

The assembler consists of 3 modules: `parser`, `coder`, and `sym_table`.

### `parser`

The parser module is responsible for parsing each line of the assembly program into its underlying fields. It also removes all white space and comments.

The parser module is implemented as a class called `parser` in namespace `hack::assembler`. The constructor receives as an argument an input file path. The parser reads the input stream, parses each line, and provides convenient access to the fields and symbols contained in the line.

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

**API documentation:**

```cpp
parser(const std::string& file_path);
```

The constructor receives as an argument the path to the input file and gets the file ready to parse.

---

```cpp
command_type command() const;
```

Returns the type of the current command. The command types are:

```cpp
enum class command_type {
    A_COMMAND, // @Xxx where Xxx is either a symbol or a decimal number
    C_COMMAND, // dest=comp;jump
    L_COMMAND // (Xxx) where Xxx is a symbol
};
```

---

```cpp
bool more_commands() const;
```

Returns true if there are more commands in the input.

---

```cpp
void advance();
```

Reads the next command from the input and makes it the current command. Should be called only if `more_commands()` is true. Initially there is no current command.

---

```cpp
std::string symbol() const;
```

Returns the symbol or decimal Xxx of the current command @Xxx or (Xxx). Should be called only when `command() == command_type::A_COMMAND` or `command() == command_type::L_COMMAND`.

---

```cpp
std::string dest() const;
```

Returns the dest mnemonic in the current C-command (8 possibilities). Should be called only when `command() == command_type::C_COMMAND`.

---

```cpp
std::string comp() const;
```

Returns the comp mnemonic in the current C-command (28 possibilities). Should be called only when `command() == command_type::C_COMMAND`.

---

```cpp
std::string jump() const;
```

Returns the jump mnemonic in the current C-command (8 possibilities). Should be called only when `command() == command_type::C_COMMAND`.

### `coder`

The coder module is responsible for translating each field of the parsed command into its corresponding binary value according to the Hack machine language specification.

The coder module is implemented as a class called `coder` in namespace `hack::assembler`. The constructor receives as an argument an output file path. The coder writes the translated binary code into the output file.

The coder class provides the following API:

```cpp
class coder {
public:
    coder();
    std::bitset<3> dest(const std::string& mnemonic) const;
    std::bitset<7> comp(const std::string& mnemonic) const;
    std::bitset<3> jump(const std::string& mnemonic) const;
};
```

**API documentation:**

```cpp
coder();
```

The constructor gets the coder ready to translate the next command.

---

```cpp
std::bitset<3> dest(const std::string& mnemonic) const;
```

Returns the binary code of the dest mnemonic.

---

```cpp
std::bitset<7> comp(const std::string& mnemonic) const;
```

Returns the binary code of the comp mnemonic.

---

```cpp
std::bitset<3> jump(const std::string& mnemonic) const;
```

Returns the binary code of the jump mnemonic.

### `sym_table`

The symbol table module is responsible for storing the mapping between symbolic labels and numeric addresses. It also provides convenient access to the symbols contained in the table.

The symbol table module is implemented as a class called `sym_table` in namespace `hack::assembler`. The constructor receives no arguments. The symbol table is initialized to include all the predefined symbols and their pre-allocated RAM addresses.

The symbol table class provides the following API:

```cpp
class sym_table {
public:
    sym_table();
    void add_entry(const std::string& symbol, std::size_t address);
    bool contains(const std::string& symbol) const;
    std::size_t address(const std::string& symbol) const;
};
```

**API documentation:**

```cpp
sym_table();
```

The constructor creates a new empty symbol table.

---

```cpp
void add_entry(const std::string& symbol, std::size_t address);
```

Adds the pair (symbol, address) to the table.

---

```cpp
bool contains(const std::string& symbol) const;
```

Returns true if the symbol table contains the given symbol.

---

```cpp
std::size_t address(const std::string& symbol) const;
```

Returns the address associated with the symbol.

## Implementation

The assembler works in two passes over the source code. In the first pass, it builds the symbol table. In the second pass, it translates the source code into binary code.

In total, the assembler has three stages:

- **Initialization**: the assembler first initializes the symbol table with the predefined symbols and their preallocated RAM addresses.
- **First pass**: Go through the entire assembly program, line by line, and build the symbol table without generating any code. As it marches through the program lines, keep a running number recording the ROM address into which the current command will be eventually loaded. This number starts at 0 and is incremented by 1 whenever a C-instruction or an A-instruction is encountered, but does not change when a label pseudocommand or a comment is encountered. Each time a pseudocommand (Xxx)
is encountered, add a new entry to the symbol table, associating Xxx with the ROM address that will eventually store the next command in the program. This pass results in entering all the program’s labels along with their ROM addresses into the symbol table. The program’s variables are handled in the second pass.
- **Second pass**: Go again through the entire program, line by line, and translate each instruction into its corresponding binary code. When encountering a pseudocommand of the form (Xxx), look up Xxx in the symbol table and use the resulting ROM address to complete the command’s translation. When encountering a pseudocommand of the form @Xxx, look up Xxx in the symbol table and use the resulting RAM address to complete the command’s translation. When encountering a C-instruction, use the predefined binary codes for dest, comp, and jump to complete the command’s translation.

## Test Strategy

The assembler is tested using the following strategy:

- **Unit tests**: The parser, coder, and symbol table modules are tested using unit tests.
- **Integration tests**: The assembler is tested using integration tests. The integration tests are divided into two groups: tests for programs without variables and tests for programs with variables.
- **Test programs**: The assembler is tested using the programs in the `test_programs` directory.

### Unit tests

### Integration tests
