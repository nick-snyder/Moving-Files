/*
 * assemble.c - handles the details of assembly for the asx20 assembler
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "defs.h"
#include "symtab.h"

#define ERROR_PROGRAM_SIZE "Program consumes more than 2^20 words"  //
#define ERROR_LABEL_DEFINED "Label %s already defined"  //
#define ERROR_OPCODE_UNKNOWN "Unknown Opcode %s"    //
#define ERROR_OPERAND_FORMAT "Opcode does not match the given operands" //
#define ERROR_CONSTANT_ZERO "Constant must be greater than zero"    //
#define ERROR_CONSTANT_INVALID "Constant %d will not fit into 20 bits"  //
#define ERROR_OFFSET_INVALID "Offset %d will not fit into 16 bits"  //
#define ERROR_MULTIPLE_EXPORT "Symbol %s exported more than once"   // 
#define ERROR_MULTIPLE_IMPORT "Symbol %s imported more than once"   // 
#define ERROR_LABEL_REFERENCE_NOT_FOUND "Label %s is referenced but not defined or imported"    //
#define ERROR_SYMBOL_IMPORT_EXPORT "Symbol %s is both imported and exported"    //
#define ERROR_SYMBOL_IMPORT_DEFINED "Symbol %s is both imported and defined"    //
#define ERROR_SYMBOL_IMPORT_NO_REFERENCE "Symbol %s is imported but not referenced" //
#define ERROR_SYMBOL_EXPORT_NO_DEFINITION "Symbol %s is exported but not defined"   //
#define ERROR_SYMBOL_IMPORT_SIZE "Symbol %s is imported and longer than 16 characters"  //
#define ERROR_SYMBOL_EXPORT_SIZE "Symbol %s is exported and longer than 16 characters"  //
#define ERROR_LABEL_SIZE16 "Reference to label %s at address %d won't fit in 16 bits"   //
#define ERROR_LABEL_SIZE20 "Reference to label %s at address %d won't fit in 20 bits"   //

// enable debugging printout
#define DEBUG 0

#define MAX_REFERENCES 100

typedef struct Data
{
    int address;                    // address defined at
    int isReferenced;               // how many times its referenced
    int isExported;                 // if its exported
    int isImported;                 // if its imported
    int isDefined;                  // if it get defined
    int isInsymbol;                 // if it qualifies as an insymbol
    int isOutsymbol;                // if it qualifies as an outsymbol
    int addressesReferenced[MAX_REFERENCES];    // each address that its referenced at
}
Data;

typedef struct Opcode
{
    char* instruction;
    int format;
    unsigned char encoding;
}
Opcode;

static Opcode opcodes[] = 
{
    {"halt", 1, 0x00},
    {"load", 5, 0x01},
    {"store", 5, 0x02},
    {"ldimm", 4, 0x03},
    {"ldaddr", 5, 0x04},
    {"ldind", 7, 0x05},
    {"stind", 7, 0x06},
    {"addf", 6, 0x07},
    {"subf", 6, 0x08},
    {"divf", 6, 0x09},
    {"mulf", 6, 0x0A},
    {"addi", 6, 0x0B},
    {"subi", 6, 0x0C},
    {"divi", 6, 0x0D},
    {"muli", 6, 0x0E},
    {"call", 2, 0x0F},
    {"ret", 1, 0x10},
    {"blt", 8, 0x11},
    {"bgt", 8, 0x12},
    {"beq", 8, 0x13},
    {"jmp", 2, 0x14},
    {"cmpxchg", 8, 0x15},
    {"getpid", 3, 0x16},
    {"getpn", 3, 0x17},
    {"push", 3, 0x18},
    {"pop", 3, 0x19}
};

static int pass = 1;
static unsigned int pc = 0;
static int errorCount = 0;
static int insymbolCount = 0;
static int outsymbolCount = 0;

static FILE *f;

void *symtab;

static void *checkSymbol(char *);
static void *addLabel(Data *, const char *);
static void errorCheck(Data *, const char *);
static void printLabel(Data *, const char *);

/**
 * Questions:
    import/export number 
    wordCount error
    label size error
    import/export size error 
 */

// this is called once so that the assembler can initialize any internal
// data structures, such as the symbol table
void initAssemble(void)
{
    symtab = symtabCreate(100);
}

// this is the "guts" of the assembler and is called for each line
// of the input that contains a label, instruction or directive
//
// note that there may be both a label and an instruction or directive
// present on a line
//
// note that the assembler directives "export" and "import" have structure
// identical to instructions with format 2, so that format is used for them
//
// for the directives "word" and "alloc" a special format, format 9, is used
//
// see defs.h for the details on how each instruction format is represented
// in the INSTR struct.
//

    // DONE: fix bad addresses. Current addresses are too low sometimes
    // fix segmentation fault in gradescope

void assemble(char *label, INSTR instr)     // pass 1: store symbol and address. pass 2: store hex code
{
    // check if label is already in table
    // add label to table if not
    Data *data = checkSymbol(label);

    if (pass == 1)
    {
        if (instr.format == 1)
        {
            if (strcmp(instr.opcode, "halt") == 0 || 
                strcmp(instr.opcode, "ret") == 0)
            {
                // normal behavior

                
            }
            else
            {
                error(ERROR_OPERAND_FORMAT);
                errorCount++;
            }

            // increment program counter
            pc++;
        }
        else if (instr.format == 2)
        {
            if (strcmp(instr.opcode, "call") == 0 || 
                strcmp(instr.opcode, "jmp") == 0)
            {
                // normal behavior

                // look for address in symtab
                data = symtabLookup(symtab, instr.u.format2.addr);

                // if data is not found
                if (!data)
                {
                    // data is not found, add it to the table
                    data = addLabel(data, instr.u.format2.addr);
                }
                
                // address where the data is referenced
                data->addressesReferenced[data->isReferenced] = pc;

                // label is referenced
                data->isReferenced++;

                if (pc > 0xfffff)
                {
                    error(ERROR_LABEL_SIZE20, instr.u.format2.addr, pc);
                    errorCount++;
                }

                // increment program counter
                pc++;
            }
            else if ((strcmp(instr.opcode, "export") == 0) 
                  || (strcmp(instr.opcode, "import") == 0))
            {
                // look for address in symtab
                data = symtabLookup(symtab, instr.u.format2.addr);

                // if data is not found
                if (!data)
                {
                    // error check
                    if (*instr.u.format2.addr > 0xffff)
                    {
                        error(ERROR_SYMBOL_EXPORT_SIZE, instr.u.format2.addr);
                        errorCount++;
                    }

                    // add symbol to table
                    data = addLabel(data, instr.u.format2.addr);
                }

                if (strcmp(instr.opcode, "export") == 0) 
                {
                    // set data to exported
                    data->isExported++;
                }
                else
                {
                    // set data to imported
                    data->isImported++;  
                }
            }
            else
            {
                error(ERROR_OPERAND_FORMAT);
                errorCount++;
            }
        }
        else if (instr.format == 3)
        {
            if (strcmp(instr.opcode, "getpid") == 0 || 
                strcmp(instr.opcode, "getpn") == 0 || 
                strcmp(instr.opcode, "push") == 0 || 
                strcmp(instr.opcode, "pop") == 0)
            {
                // normal behavior
            }
            else
            {
                error(ERROR_OPERAND_FORMAT);
                errorCount++;
            }

            // increment program counter
            pc++;
        }
        else if (instr.format == 4)
        {
            if (strcmp(instr.opcode, "ldimm") == 0)
            {
                // normal behavior

                if (instr.u.format4.constant > 0xfffff)
                {
                    error(ERROR_CONSTANT_INVALID, instr.u.format4.constant);
                    errorCount++;
                }
            }
            else
            {
                error(ERROR_OPERAND_FORMAT);
                errorCount++;
            }

            // increment program counter
            pc++;
        }
        else if (instr.format == 5)
        {
            if (strcmp(instr.opcode, "load") == 0 || 
                strcmp(instr.opcode, "store") == 0 || 
                strcmp(instr.opcode, "ldaddr") == 0)
            {
                // normal behavior

                // look for address in symtab
                data = symtabLookup(symtab, instr.u.format5.addr);

                // if data is not found
                if (!data)
                {
                    // data is not found, add it to the table
                    data = addLabel(data, instr.u.format5.addr);
                }
                
                // address where the data is referenced
                data->addressesReferenced[data->isReferenced] = pc;

                // data was refernced here
                data->isReferenced++;

                if (pc > 0xfffff)
                {
                    error(ERROR_LABEL_SIZE20, instr.u.format5.addr, pc);
                    errorCount++;
                }
            }
            else
            {
                error(ERROR_OPERAND_FORMAT);
                errorCount++;
            }

            // increment program counter
            pc++;
        }
        else if (instr.format == 6)
        {
            if (strcmp(instr.opcode, "addf") == 0 || 
                strcmp(instr.opcode, "subf") == 0 || 
                strcmp(instr.opcode, "divf") == 0 || 
                strcmp(instr.opcode, "mulf") == 0 || 
                strcmp(instr.opcode, "addi") == 0 || 
                strcmp(instr.opcode, "subi") == 0 || 
                strcmp(instr.opcode, "divi") == 0 || 
                strcmp(instr.opcode, "muli") == 0)
            {
                // normal behavior

                
            }
            else
            {
                error(ERROR_OPERAND_FORMAT);
                errorCount++;
            }

            // increment program counter
            pc++;
        }
        else if (instr.format == 7)
        {
            if (strcmp(instr.opcode, "ldind") == 0 || 
                strcmp(instr.opcode, "stind") == 0)
            {
                // normal behavior

                if (instr.u.format7.offset > 0xffff)
                {
                    error(ERROR_CONSTANT_INVALID);
                    errorCount++;
                }
            }
            else
            {
                error(ERROR_OPERAND_FORMAT);
                errorCount++;
            }

            // increment program counter
            pc++;
        }
        else if (instr.format == 8)
        {
            if (strcmp(instr.opcode, "blt") == 0 || 
                strcmp(instr.opcode, "bgt") == 0 || 
                strcmp(instr.opcode, "beq") == 0 || 
                strcmp(instr.opcode, "cmpxchg") == 0)
            {
                // normal behavior

                // look for address in symtab
                data = symtabLookup(symtab, instr.u.format8.addr);

                // if data is not found
                if (!data)
                {
                    // data is not found, add it to the table
                    data = addLabel(data, instr.u.format8.addr);
                }

                // address where the data is referenced
                data->addressesReferenced[data->isReferenced] = pc;

                // data was refernced here
                data->isReferenced++;

                if (pc > 0xffff)
                {
                    error(ERROR_LABEL_SIZE16, instr.u.format8.addr, pc);
                    errorCount++;
                }
            }
            else
            {
                error(ERROR_OPERAND_FORMAT);
                errorCount++;
            }     

            // increment program counter
            pc++;           
        }
        else if (instr.format == 9)
        {
            if (strcmp(instr.opcode, "word") == 0)
            {
                // increment program counter
                pc++;

                // if (instr.u.format9.constant > 0xfffff)
                // {
                //     error(ERROR_CONSTANT_INVALID, instr.u.format9.constant);
                //     errorCount++;
                // }
            }
            else if (strcmp(instr.opcode, "alloc") == 0)
            {
                pc += instr.u.format9.constant;

                if (instr.u.format9.constant == 0)
                {
                    error(ERROR_CONSTANT_ZERO);
                    errorCount++;
                }
            }
            else
            {
                error(ERROR_OPERAND_FORMAT);
                errorCount++;
            }
        }
        else
        {
            if (instr.format != 0)
            {
                error(ERROR_OPCODE_UNKNOWN, instr.opcode);
                errorCount++;
            }
        }
    }
    else
    {
        if (instr.format == 1)
        {
            unsigned int op;

            if (strcmp(instr.opcode, "halt") == 0)
            {
                op = opcodes[0].encoding;
            }

            if (strcmp(instr.opcode, "ret") == 0)
            {
                op = opcodes[16].encoding;
            }

            putc(op & 0xff, f);

            putc(0x00, f);
            putc(0x00, f);
            putc(0x00, f);

            pc++;
        }
        else if (instr.format == 2)
        {
            if (strcmp(instr.opcode, "export") != 0 && 
                strcmp(instr.opcode, "import") != 0)
            {
                Data* data = symtabLookup(symtab, instr.u.format2.addr);
                
                unsigned int addr = data->address - pc;
                unsigned int op;

                if (strcmp(instr.opcode, "call") == 0)
                {
                    op = opcodes[15].encoding;

                    addr = 0;
                }

                if (strcmp(instr.opcode, "jmp") == 0)
                {
                    op = opcodes[20].encoding;
                    addr--;
                }

                putc(op & 0xff, f);

                putc(((addr << 4) | 0x00) & 0xff, f);

                putc((addr >> 4) & 0xff, f);
                putc((addr >> 12) & 0xff, f);

                pc++;
            }
        }
        else if (instr.format == 3)
        {
            unsigned int op;
            unsigned int reg = instr.u.format3.reg;

            if (strcmp(instr.opcode, "getpid") == 0)
            {
                op = opcodes[22].encoding;
            }
            if (strcmp(instr.opcode, "getpn") == 0)
            {
                op = opcodes[23].encoding;
            }
            if (strcmp(instr.opcode, "push") == 0)
            {
                op = opcodes[24].encoding;
            }
            if (strcmp(instr.opcode, "pop") == 0)
            {
                op = opcodes[25].encoding;
            }

            putc(op & 0xff, f);

            putc(reg & 0xff, f);

            putc(0x00, f);
            putc(0x00, f);

            pc++;
        }
        else if (instr.format == 4)
        {
            unsigned int op;
            unsigned int reg = instr.u.format4.reg;
            unsigned int constant = instr.u.format4.constant;

            if (strcmp(instr.opcode, "ldimm") == 0)
            {
                op = opcodes[3].encoding;
            }

            putc(op & 0xff, f);

            putc(((constant << 4) | reg) & 0xff, f);

            putc((constant >> 4) & 0xff, f);
            putc((constant >> 12) & 0xff, f);

            pc++;
        }
        else if (instr.format == 5)
        {
            Data* data = symtabLookup(symtab, instr.u.format5.addr);

            unsigned int op;
            unsigned int addr = data->address - pc - 1;
            unsigned int reg = instr.u.format5.reg;
            
            if (strcmp(instr.opcode, "load") == 0)
            {
                op = opcodes[1].encoding;
            }
            
            if (strcmp(instr.opcode, "store") == 0)
            {
                op = opcodes[2].encoding;
            }

            if (strcmp(instr.opcode, "ldaddr") == 0)
            {
                op = opcodes[4].encoding;
            }

            putc(op & 0xff, f);

            putc(((addr << 4) | reg) & 0xff, f);

            putc((addr >> 4) & 0xff, f);
            putc((addr >> 12) & 0xff, f);

            pc++;
        }
        else if (instr.format == 6)
        {
            unsigned int reg1 = instr.u.format6.reg1;
            unsigned int reg2 = instr.u.format6.reg2;
            unsigned int op;

            if (strcmp(instr.opcode, "addf") == 0)
            {
                op = opcodes[7].encoding;
            } 

            if (strcmp(instr.opcode, "subf") == 0)
            {
                op = opcodes[8].encoding;
            } 

            if (strcmp(instr.opcode, "divf") == 0)
            {
                op = opcodes[9].encoding;
            } 

            if (strcmp(instr.opcode, "mulf") == 0)
            {
                op = opcodes[10].encoding;
            } 

            if (strcmp(instr.opcode, "addi") == 0)
            {
                op = opcodes[11].encoding;
            } 

            if (strcmp(instr.opcode, "subi") == 0)
            {
                op = opcodes[12].encoding;
            } 

            if (strcmp(instr.opcode, "divi") == 0)
            {
                op = opcodes[13].encoding;
            } 

            if (strcmp(instr.opcode, "muli") == 0)
            {
                op = opcodes[14].encoding;
            }

            putc(op & 0xff, f);

            putc(((reg2 << 4) | reg1) & 0xff, f);

            putc(0x00, f);
            putc(0x00, f);

            pc++;
        }
        else if (instr.format == 7)
        {
            unsigned int offset = instr.u.format7.offset;
            unsigned int reg1 = instr.u.format7.reg1;
            unsigned int reg2 = instr.u.format7.reg2;
            unsigned int op;

            if (strcmp(instr.opcode, "ldind") == 0)
            {
                op = opcodes[5].encoding;
            } 

            if (strcmp(instr.opcode, "stind") == 0)
            {
                op = opcodes[6].encoding;
            } 

            putc(op & 0xff, f);

            putc(((reg2 << 4) | reg1) & 0xff, f);

            putc(offset & 0xff, f);
            putc((offset >> 8) & 0xff, f);

            pc++;
        }
        else if (instr.format == 8)
        {
            Data* data = symtabLookup(symtab, instr.u.format8.addr);
            
            unsigned int addr = data->address - pc - 1;
            unsigned int reg1 = instr.u.format8.reg1;
            unsigned int reg2 = instr.u.format8.reg2;
            unsigned int op;

            if (strcmp(instr.opcode, "blt") == 0)
            {
                op = opcodes[17].encoding;
            } 

            if (strcmp(instr.opcode, "bgt") == 0)
            {
                op = opcodes[18].encoding;
            } 

            if (strcmp(instr.opcode, "beq") == 0)
            {
                op = opcodes[19].encoding;
            } 

            if (strcmp(instr.opcode, "cmpxchg") == 0)
            {
                op = opcodes[21].encoding;
            } 

            putc(op & 0xff, f);

            putc(((reg2 << 4) | reg1) & 0xff, f);

            putc(addr & 0xff, f);
            putc((addr >> 8) & 0xff, f);

            // printf("%x\n", (0x00000000 & op) & (reg1 << 4) & (reg2 << 8) & (addr << 12));
            // printf("%x %x %x %x\n", op, reg1, reg2, addr);

            pc++;
        }
        else if (instr.format == 9)
        {
            unsigned int constant = instr.u.format9.constant;

            if (strcmp(instr.opcode, "word") == 0)
            {
                pc++;

                for (int i = 0; i < 4; i++)
                {
                    putc(constant & 0xff, f);
                    constant >>= 8;
                }
            }
            
            if (strcmp(instr.opcode, "alloc") == 0)
            {
                pc += instr.u.format9.constant;

                for (int i = 0; i < instr.u.format9.constant; i++)
                {
                    putc(0x00, f);
                    // constant >>= 8;
                }
            }
            
            
        }
    }
}

// this is called between passes and provides the assembler the file
// pointer to use for outputing the object file
//
// it returns the number of errors seen on pass1
//
int betweenPasses(FILE *outf)
{
    f = outf;

    void* iterator = symtabCreateIterator(symtab);
    const char* label;
    void* returnData;

    // error checking and printing every label in the table
    while ((label = symtabNext(iterator, &returnData)))
    {
        Data* data = returnData;

        errorCheck(data, label);

        printLabel(data, label);

        if (data->isExported != 0)
        {
            data->isInsymbol++;
            insymbolCount++;
        }

        if (data->isImported != 0)
        {
            data->isOutsymbol++;
            outsymbolCount += data->isReferenced;
        }
    }

    if ((pass == 1) && (errorCount == 0))
    {
        // build object file
        unsigned int insymbolCountWord = insymbolCount * 5;
        unsigned int outsymbolCountWord = outsymbolCount * 5;
        unsigned int objectFileLength = pc;
        
        // length of Insymbol section
        for (int i = 0; i < 4; i++)
        {
            putc(insymbolCountWord & 0xff, f); // Syscall param write(buf) points to uninitialised byte(s)
            insymbolCountWord >>= 8;
        }

        // length of Outsymbol section
        for (int i = 0; i < 4; i++)
        {
            putc(outsymbolCountWord & 0xff, f); // Syscall param write(buf) points to uninitialised byte(s)
            outsymbolCountWord >>= 8;
        }

        // Length of Object code
        for (int i = 0; i < 4; i++)
        {
            putc(objectFileLength & 0xff, f); // Syscall param write(buf) points to uninitialised byte(s)
            objectFileLength >>= 8;
        }

        // Insymbols
        // go through symtab and if data->isInsymbol > 0, add "x3 4" to object file

        // create new iterator
        iterator = symtabCreateIterator(symtab);
        
        // for each label in the symbol table
        while ((label = symtabNext(iterator, &returnData)))
        {
            // data is from the current label
            Data* data = returnData;

            // if the label is an insymbol...
            if (data->isInsymbol > 0)
            {                
                // add the label to the object file
                for (int i = 0; i < 16; i++)
                {
                    // if the current char is viable
                    if (label[i])
                    {
                        // put every char of the label
                        putc(label[i], f);
                    }
                    else
                    {
                        // fill the rest of the word with zeros
                        putc(0x00, f);
                    }
                }
                
                // save a copy of the label's address
                int ad = data->address;

                // add the label's address to the object file
                for (int i = 0; i < 4; i++)
                {
                    // put in char by char
                    putc(ad & 0xff, f);

                    // shift to the next char
                    ad >>= 8;
                }
            }
        }

        // Outsymbols
        // go through symtab and if data->isOutsymbol > 0, add "x3 4" to object file

        // create new iterator
        iterator = symtabCreateIterator(symtab);
        
        // for each label in the symbol table
        while ((label = symtabNext(iterator, &returnData)))
        {
            // data is from the current label
            Data* data = returnData;

            // if the label is an insymbol...
            if (data->isOutsymbol > 0)
            {                
                // add the label for each time it is referenced and at what address
                for (int i = 0; i < data->isReferenced; i++)
                {
                    // add the label to the object file
                    for (int i = 0; i < 16; i++)
                    {
                        // if the current char is viable
                        if (label[i])
                        {
                            // put every char of the label
                            putc(label[i], f);
                        }
                        else
                        {
                            // fill the rest of the word with zeros
                            putc(0x00, f);
                        }
                    }

                    // add the address where the label is referenced

                    // save a copy of the label's address
                    int ad = data->addressesReferenced[i];
                    
                    // add the label's address to the object file
                    for (int i = 0; i < 4; i++)
                    {
                        // put in char by char
                        putc(ad & 0xff, f);

                        // shift to the next char
                        ad >>= 8;
                    }
                }
            }
        }
    }

    pc = 0;
    pass = 2;

    return errorCount;
}

static void *checkSymbol(char *label)
{
    Data *data;

    if (label)
    {            
        // look for label in symtab
        data = symtabLookup(symtab, label);

        // if data is found
        if (data)
        {
            // label is now defined at this address
            data->address = pc;
        }

        // if not found, add new entry
        else
        {   
            data = addLabel(data, label);
        }

        data->isDefined++;
    }

    return data;
}

static void *addLabel(Data *data, const char *label)
{
    // label not found; insert new label that is referenced
    data = malloc(sizeof *data);
    if (!data)
    {
        printf("malloc failed!!!\n");
    }

    data->address = pc;
    data->isReferenced = 0; 
    data->isExported = 0;
    data->isImported = 0;
    data->isDefined = 0;
    data->isInsymbol = 0;
    data->isOutsymbol = 0;

    for (int i = 0; i < MAX_REFERENCES; i++)
    {
        if (i == 0)
        {
            data->addressesReferenced[i] = pc;
        }
        else
        {
            data->addressesReferenced[i] = -1;
        }
    }

    symtabInstall(symtab, label, data);

    // make sure insertion was successful
    if (!symtabLookup(symtab, label))
    {
        printf("'%s' failed to be installed\n", label);
    }

    return data;
}

static void errorCheck(Data *data, const char *label)
{
    if (pc > 0xfffff)
    {
        error(ERROR_PROGRAM_SIZE);
        errorCount++;
    }
    if (data->isDefined > 1)
    {
        error(ERROR_LABEL_DEFINED, label);
        errorCount++;
    }
    if (data->isImported == 1 && 
        data->isExported == 1)
    {
        error(ERROR_SYMBOL_IMPORT_EXPORT, label);
        errorCount++;
    }
    if (data->isImported == 1 && 
        data->isDefined == 1)
    {
        error(ERROR_SYMBOL_IMPORT_DEFINED, label);
        errorCount++;
    }
    if (data->isImported == 1 && 
        data->isReferenced == 0)
    {
        error(ERROR_SYMBOL_IMPORT_NO_REFERENCE, label);
        errorCount++;
    }
    if (data->isExported == 1 && 
        data->isDefined == 0)
    {
        error(ERROR_SYMBOL_EXPORT_NO_DEFINITION, label);
        errorCount++;
    }
    if (data->isReferenced > 0 && 
        data->isDefined == 0 && 
        data->isImported == 0)
    {
        error(ERROR_LABEL_REFERENCE_NOT_FOUND, label);
        errorCount++;
    }
    if (data->isExported > 1)
    {
        error(ERROR_MULTIPLE_EXPORT, label);
        errorCount++;
    }
    if (data->isImported > 1)
    {
        error(ERROR_MULTIPLE_IMPORT, label);
        errorCount++;
    }
}

static void printLabel(Data *data, const char *label)
{
    printf("%s", label);

    if (!(
        (data->isReferenced > 0) && 
        (data->isDefined == 0)))
    {
        printf(" %d", data->address);
    }
    if (data->isReferenced > 0) 
    {
        printf(" reference");
    }
    if (data->isExported == 1) 
    {
        printf(" exported");
    }
    if (data->isImported == 1) 
    {
        printf(" imported");
    }
    printf("\n");
}