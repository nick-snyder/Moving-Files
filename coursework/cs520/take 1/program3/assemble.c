/*
 * assemble.c - handles the details of assembly for the asx20 assembler
 *
 *              This currently just contains stubs with debugging output.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

typedef struct Data
{
    int address;
    int isReferenced;
    int isExported;
    int isImported;
    int isDefined;
    int programCounter;
    int isInsymbol;
    int isOutsymbol;
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

static int pc = 0;
static int wordCount = 0;
static int pass = 1;
static int errorCount = 0;
static int insymbolCount = 0;
static int outsymbolCount = 0;

static FILE *f;

void *symtab;

// this is called once so that the assembler can initialize any internal
// data structures, such as the symbol table
void initAssemble(void)
{
    symtab = symtabCreate(10);
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

    // DONE: fix addresses
    // DONE: add more errors (word counts)
    // free data
    // DONE: fix missing labels
    // DONE: fix referencing (forward referencing)
    // DONE: add object file
    // DONE: add pc to pass 2 (format 5)
    // DONE: add isInsymbol member
    // DONE: add isOutsymbol member
    // fix addresses for formats 2, 4, and 5
    // DONE: fix Insymbol labels (00000079 -> 00003179)
    // fix insymbol count
    // fix mystery bytes before program section
    // fix memory errors

void assemble(char *label, INSTR instr)     // pass 1: store symbol and address. pass 2: store hex code
{
    switch (pass)
    {
        case 1:
            Data *data;

            if (label)
            {            
                // look for label in symtab
                data = symtabLookup(symtab, label);

                // if data is found
                if (data)
                {
                    // if label is in the table but already defined
                    if (data->isDefined != 0)
                    {
                        // throw an error
                        error(ERROR_LABEL_DEFINED, label);
                        errorCount++;
                    }
                    else
                    {
                        // label is now defined at this address
                        data->address = pc;
                        data->isDefined++;
                    }
                }
                else
                {   
                    // prepare new symtab entry
                    data = malloc(sizeof *data);
                    if (!data)
                    {
                        printf("malloc failed!!!\n");
                    }
                    data->address = pc;
                    data->isReferenced = 0; 
                    data->isExported = 0;   
                    data->isImported = 0;   
                    data->isDefined = 1;
                    data->isInsymbol = 0;
                    data->isOutsymbol = 0;  

                    // insert entry
                    symtabInstall(symtab, label, data);

                    // make sure insertion was successful
                    if (!symtabLookup(symtab, label))
                    {
                        printf("'%s' failed to be installed\n", label);
                    }
                }
            }

            if (instr.format != 0)
            {
                switch(instr.format)
                {
                    case 1:
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
                        break;
                    case 2:
                        if (strcmp(instr.opcode, "call") == 0 || 
                            strcmp(instr.opcode, "jmp") == 0)
                        {
                            // normal behavior

                            // look for address in symtab
                            data = symtabLookup(symtab, instr.u.format2.addr);

                            // if data is found
                            if (data)
                            {
                                if (data->address > 0xfffff)
                                {
                                    error(ERROR_LABEL_SIZE20, instr.u.format2.addr, data->address);
                                    errorCount++;
                                }
                                
                                // label is referenced
                                data->isReferenced++; // just assign as 1
                                // We don't care how many times a label is referenced
                                
                                
                                if (data->isImported == 1)
                                {
                                    outsymbolCount++;
                                }
                            }
                            else
                            {
                                // label not found; insert new label that is referenced
                                data = malloc(sizeof *data);
                                if (!data)
                                {
                                    printf("malloc failed!!!\n");
                                }
                                data->address = pc;
                                data->isReferenced = 1; 
                                data->isExported = 0;   // could be
                                data->isImported = 0;   // could be
                                data->isDefined = 0;    // not yet
                                data->isInsymbol = 0;
                                data->isOutsymbol = 0;
                                symtabInstall(symtab, instr.u.format2.addr, data);
                            }
                            pc++;
                        }
                        else if (strcmp(instr.opcode, "export") == 0)
                        {
                            // look for address in symtab
                            data = symtabLookup(symtab, instr.u.format2.addr);

                            // if data is found
                            if (data)
                            {
                                // if the address is already exported
                                if (data->isExported > 0)
                                {
                                    // throw an error
                                    error(ERROR_MULTIPLE_EXPORT, instr.u.format2.addr);
                                    errorCount++;
                                }
                                else
                                {
                                    data->isExported++;
                                    insymbolCount++;
                                }
                            }
                            else
                            {
                                if (*instr.u.format2.addr > 0xffff)
                                {
                                    error(ERROR_SYMBOL_EXPORT_SIZE, instr.u.format2.addr);
                                    errorCount++;
                                }
                                // label not found; insert new label that is exported
                                data = malloc(sizeof *data);
                                if (!data)
                                {
                                    printf("malloc failed!!!\n");
                                }
                                data->address = pc;
                                data->isReferenced = 0; // could be
                                data->isExported = 1;   
                                data->isImported = 0;   // couldn't be
                                data->isDefined = 0;    // not yet
                                data->isInsymbol = 0;
                                data->isOutsymbol = 0;
                                symtabInstall(symtab, instr.u.format2.addr, data);
                            }
                        }
                        else if (strcmp(instr.opcode, "import") == 0)
                        {
                            if (pass == 1)
                            {
                                // look for address in symtab
                                data = symtabLookup(symtab, instr.u.format2.addr);

                                // if data is found
                                if (data)
                                {
                                    // if the address is already imported
                                    if (data->isImported > 0)
                                    {
                                        // throw an error
                                        error(ERROR_MULTIPLE_IMPORT, instr.u.format2.addr);
                                        errorCount++;
                                    }
                                    else
                                    {
                                        data->isImported++;
                                        outsymbolCount++;
                                    }
                                }
                                else
                                {
                                    if (*instr.u.format2.addr > 0xffff)
                                    {
                                        error(ERROR_SYMBOL_IMPORT_SIZE, instr.u.format2.addr);
                                        errorCount++;
                                    }

                                    // label not found; insert new label that is exported
                                    data = malloc(sizeof *data);
                                    if (!data)
                                    {
                                        printf("malloc failed!!!\n");
                                    }
                                    data->address = pc;
                                    data->isReferenced = 0; // could be
                                    data->isExported = 0;   // couldn't be
                                    data->isImported = 1;   
                                    data->isDefined = 0;    // not yet
                                    data->isInsymbol = 0;
                                    data->isOutsymbol = 0;
                                    symtabInstall(symtab, instr.u.format2.addr, data);
                                }
                                // outsymbolCount++;
                            }
                        }
                        else
                        {
                            error(ERROR_OPERAND_FORMAT);
                            errorCount++;
                        }

                        break;
                    case 3:
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

                        pc++;

                        break;
                    case 4:
                        if (strcmp(instr.opcode, "ldimm") == 0)
                        {
                            // normal behavior
                        }
                        else
                        {
                            error(ERROR_OPERAND_FORMAT);
                            errorCount++;
                        }

                        if (instr.u.format4.constant > 0xfffff)
                        {
                            error(ERROR_CONSTANT_INVALID, instr.u.format4.constant);
                            errorCount++;
                        }

                        pc++;
                        
                        break;
                    case 5:

                        if (strcmp(instr.opcode, "load") == 0 || 
                            strcmp(instr.opcode, "store") == 0 || 
                            strcmp(instr.opcode, "ldaddr") == 0)
                        {
                            // normal behavior

                            // look for address in symtab
                            data = symtabLookup(symtab, instr.u.format5.addr);

                            // if data is found
                            if (data)
                            {
                                if (data->address > 0xfffff)
                                {
                                    error(ERROR_LABEL_SIZE20, instr.u.format5.addr, data->address);
                                    errorCount++;
                                }

                                // label is referenced
                                data->isReferenced++; // just assign as 1
                                // We don't care how many times a label is referenced
                                
                                
                                if (data->isImported == 1)
                                {
                                    outsymbolCount++;
                                }
                            }
                            else
                            {
                                // label not found; insert new label that is referenced
                                data = malloc(sizeof *data);
                                if (!data)
                                {
                                    printf("malloc failed!!!\n");
                                }
                                data->address = pc;
                                data->isReferenced = 1; 
                                data->isExported = 0;   // could be
                                data->isImported = 0;   // could be
                                data->isDefined = 0;    // not yet
                                data->isInsymbol = 0;
                                data->isOutsymbol = 0; 
                                symtabInstall(symtab, instr.u.format5.addr, data);
                            }
                        }
                        else
                        {
                            error(ERROR_OPERAND_FORMAT);
                            errorCount++;
                        }

                        pc++;
                        
                        break;
                    case 6:
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

                        pc++;

                        break;
                    case 7:
                        if (strcmp(instr.opcode, "ldind") == 0 || 
                            strcmp(instr.opcode, "stind") == 0)
                        {
                            // normal behavior
                        }
                        else
                        {
                            error(ERROR_OPERAND_FORMAT);
                            errorCount++;
                        }

                        if (instr.u.format7.offset > 0xffff)
                        {
                            error(ERROR_CONSTANT_INVALID);
                            errorCount++;
                        }

                        pc++;

                        break;
                    case 8:
                        if (strcmp(instr.opcode, "blt") == 0 || 
                            strcmp(instr.opcode, "bgt") == 0 || 
                            strcmp(instr.opcode, "beq") == 0 || 
                            strcmp(instr.opcode, "cmpxchg") == 0)
                        {
                            // normal behavior

                            // look for address in symtab
                            data = symtabLookup(symtab, instr.u.format8.addr);

                            // if data is found
                            if (data)
                            {
                                if (data->address > 0xffff)
                                {
                                    error(ERROR_LABEL_SIZE16, instr.u.format8.addr, data->address);
                                    errorCount++;
                                }
                                // label is referenced
                                data->isReferenced = 1; // just assign as 1
                                // We don't care how many times a label is referenced

                                // if some data is 
                                if (data->isImported == 1)
                                {
                                    outsymbolCount++;
                                }
                            }
                            else
                            {
                                // label not found; insert new label that is referenced
                                data = malloc(sizeof *data);
                                if (!data)
                                {
                                    printf("malloc failed!!!\n");
                                }
                                data->address = pc;
                                data->isReferenced = 1; 
                                data->isExported = 0;   // could be
                                data->isImported = 0;   // could be
                                data->isDefined = 0;    // not yet  
                                data->isInsymbol = 0;
                                data->isOutsymbol = 0;
                                symtabInstall(symtab, instr.u.format8.addr, data);
                            }
                        }
                        else
                        {
                            error(ERROR_OPERAND_FORMAT);
                            errorCount++;
                        }

                        pc++;

                        break;
                    case 9:
                        if (strcmp(instr.opcode, "word") == 0)
                        {
                            wordCount++;
                            pc++;

                            if (instr.u.format9.constant > 0xfffff)
                            {
                                error(ERROR_CONSTANT_INVALID);
                            }
                        }
                        else if (strcmp(instr.opcode, "alloc") == 0)
                        {
                            wordCount++;
                            pc = pc + instr.u.format9.constant - 1;

                            if (instr.u.format9.constant <= 0)
                            {
                                error(ERROR_CONSTANT_ZERO);
                            }
                        }
                        else
                        {
                            error(ERROR_OPERAND_FORMAT);
                            errorCount++;
                        }

                        break;
                    default:
                        error(ERROR_OPCODE_UNKNOWN, instr.opcode);
                        errorCount++;
                        // bug("unexpected instruction format (%d) in assemble", instr.format);
                        break;
                }
            }
            break;
        case 2:
            Data* addressData;
            int ad;             // address
            unsigned char r1;   // register #1
            unsigned char r2;   // register #2
            unsigned char of;   // offset
            unsigned char co;   // constant
            unsigned char op;   // operation/opcode
            unsigned char t;    // temp

            switch(instr.format)
            {
                case 1:

                    if (strcmp(instr.opcode, "halt") == 0)
                    {
                        op = opcodes[0].encoding;
                    }

                    if (strcmp(instr.opcode, "ret") == 0)
                    {
                        op = opcodes[16].encoding;
                    }

                    putc(op, f);

                    putc(0x00, f);
                    putc(0x00, f);
                    putc(0x00, f);
                    
                    break;
                case 2:                  
                    if (strcmp(instr.opcode, "export") != 0 || 
                        strcmp(instr.opcode, "import") != 0)
                    {
                        addressData = symtabLookup(symtab, instr.u.format2.addr);
                        ad = addressData->address - pc;

                        if (strcmp(instr.opcode, "call") == 0)
                        {
                            op = opcodes[15].encoding;

                            ad = 0;
                        }

                        if (strcmp(instr.opcode, "jmp") == 0)
                        {
                            op = opcodes[20].encoding;
                        }

                        putc(op, f);

                        t = ad << 4;
                        t |= 0x0;
                        putc(t, f);

                        t = ad >> 4;
                        putc(t, f);

                        t = ad >> 12;
                        putc(t, f);

                        pc++;
                    }

                    break;
                case 3:
                    r1 = instr.u.format3.reg;

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

                    putc(op, f);

                    putc(r1 | 0x00, f);

                    putc(0x00, f);
                    putc(0x00, f);

                    pc++;
                    
                    break;
                case 4:
                    co = instr.u.format4.constant;
                    r1 = instr.u.format4.reg;
                    op = opcodes[3].encoding;

                    putc(op, f);

                    t = co << 4;
                    t |= r1;
                    putc(t, f);

                    t = co >> 4;
                    putc(t, f);
                    t = co >> 12;
                    putc(t, f);

                    pc++;
                    
                    break;
                case 5:
                    addressData = symtabLookup(symtab, instr.u.format5.addr);
                    ad = addressData->address - pc + 3;
                    r1 = instr.u.format5.reg;
                    
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

                    putc(op, f);

                    t = ad << 4;
                    t |= r1;
                    putc(t, f);

                    t = ad >> 4;
                    putc(t, f);
                    t = ad >> 12;
                    putc(t, f);

                    // ffffd101	load r1, x1
                    pc++;

                    break;
                case 6:
                    r1 = instr.u.format6.reg1;
                    r2 = instr.u.format6.reg2;

                    if (strcmp(instr.opcode, "addf") == 0)
                    {
                        op = (unsigned char) opcodes[7].encoding;
                    } 

                    if (strcmp(instr.opcode, "subf") == 0)
                    {
                        op = (unsigned char) opcodes[8].encoding;
                    } 

                    if (strcmp(instr.opcode, "divf") == 0)
                    {
                        op = (unsigned char) opcodes[9].encoding;
                    } 

                    if (strcmp(instr.opcode, "mulf") == 0)
                    {
                        op = (unsigned char) opcodes[10].encoding;
                    } 

                    if (strcmp(instr.opcode, "addi") == 0)
                    {
                        op = (unsigned char) opcodes[11].encoding;
                    } 

                    if (strcmp(instr.opcode, "subi") == 0)
                    {
                        op = (unsigned char) opcodes[12].encoding;
                    } 

                    if (strcmp(instr.opcode, "divi") == 0)
                    {
                        op = (unsigned char) opcodes[13].encoding;
                    } 

                    if (strcmp(instr.opcode, "muli") == 0)
                    {
                        op = (unsigned char) opcodes[14].encoding;
                    } 

                    #if DEBUG
                        printf("r2: %x r1: %x op: %x\n", r2, r1, op);
                    #endif

                    // 0000120b	addi r2, r1

                    putc(op, f);

                    t = r2 << 4;
                    t |= r1;
                    putc(t, f);

                    putc(0x00, f);
                    putc(0x00, f);

                    pc++;

                    break;
                case 7:
                    of = instr.u.format7.offset;
                    r1 = instr.u.format7.reg1;
                    r2 = instr.u.format7.reg2;

                    if (strcmp(instr.opcode, "ldind") == 0)
                    {
                        op = opcodes[5].encoding;
                    } 

                    if (strcmp(instr.opcode, "stind") == 0)
                    {
                        op = opcodes[6].encoding;
                    } 

                    putc(op, f);

                    t = r2 << 4;
                    t |= r1;
                    putc(t, f);

                    putc(of, f);
                    t = of >> 8;
                    putc(of, f);

                    pc++;

                    break;
                case 8:
                    addressData = symtabLookup(symtab, instr.u.format8.addr);
                    ad = addressData->address - pc+2;
                    r1 = instr.u.format8.reg1;
                    r2 = instr.u.format8.reg2;

                    if (strcmp(instr.opcode, "blt") == 0)
                    {
                        op = (unsigned char) opcodes[17].encoding;
                    } 

                    if (strcmp(instr.opcode, "bgt") == 0)
                    {
                        op = (unsigned char) opcodes[18].encoding;
                    } 

                    if (strcmp(instr.opcode, "beq") == 0)
                    {
                        op = (unsigned char) opcodes[19].encoding;
                    } 

                    if (strcmp(instr.opcode, "cmpxchg") == 0)
                    {
                        op = (unsigned char) opcodes[21].encoding;
                    } 

                    putc(op, f);

                    t = r2 << 4;
                    t |= r1;
                    putc(t, f);

                    putc(ad, f);
                    t = ad >> 8;
                    putc(ad, f);

                    pc++;
                    
                    break;
                case 9:
                    co = instr.u.format9.constant;

                    if (strcmp(instr.opcode, "word") == 0)
                    {
                        pc++;
                    }
                    
                    if (strcmp(instr.opcode, "alloc") == 0)
                    {
                        pc = pc + instr.u.format9.constant - 1;
                    }

                    // fwrite(&instr.u.format9.constant, sizeof(int), 1, f);
                    

                    putc(co, f);
                    co <<= 8;
                    putc(co, f);
                    co <<= 8;
                    putc(co, f);
                    co <<= 8;
                    putc(co, f);
                    co <<= 8;

                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

// this is called between passes and provides the assembler the file
// pointer to use for outputing the object file
//
// it returns the number of errors seen on pass1
//
int betweenPasses(FILE *outf)
{

    // if (wordCount > 1048576)
    // {
    //     error(ERROR_PROGRAM_SIZE);
    // }

    f = outf;

    void* iterator = symtabCreateIterator(symtab);
    const char* label;
    void* returnData;

    // error checking and printing every label in the table
    while ((label = symtabNext(iterator, &returnData)))
    {
        Data* data = returnData;

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
        if (data->isReferenced == 1 && 
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

        if (data->isReferenced == 1) 
        {
            printf("%s %d reference\n", label, data->address);
        }
        if (data->isReferenced == 0) 
        {
            printf("%s %d \n", label, data->address);
        }

        if (data->isDefined == 1 && data->isExported == 1)
        {
            // Insymbol
            data->isInsymbol = 1;
            insymbolCount++;
        }
        if (data->isReferenced == 1 && data->isDefined == 0)
        {
            // Outsymbol
            data->isOutsymbol = 1;
            // outsymbolCount++;
        }

        #if DEBUG
            // printf("members: ");
            // printf("a%d ", data->address);
            // printf("r%d ", data->isReferenced);
            // printf("e%d ", data->isExported);   
            // printf("i%d ", data->isImported);   
            // printf("d%d ", data->isDefined);   
            // printf("in%d ", data->isInsymbol);   
            // printf("out%d\n", data->isOutsymbol); 
        #endif
    }

    if (pass == 1 && errorCount == 0)
    {
        // create *.obj file
        #if DEBUG
            printf("insymbolCount: %d\n", insymbolCount);
            printf("outsymbolCount: %d\n", outsymbolCount);
            printf("pc: %d\n", pc);
            printf("length of Insymbol section: %d\n", insymbolCount * 5);
            printf("length of Outsymbol section: %d\n", outsymbolCount * 5);
            printf("length of object code: %d\n", pc + 1);
        #endif

        int il = insymbolCount * 5;
        int ol = outsymbolCount * 5;
        int ofl = pc + 1;

        // for (size_t i = 0; i < 16; i++)
        // {
        //     if (il < i)
        //     {
        //         putc(il, f);
        //     }
        //     else
        //     {
        //         putc(0x00, f);
        //     }
        // }

        // header
        // Insymbol length
        putc(il & 0xff, f); // Syscall param write(buf) points to uninitialised byte(s)
        il <<= 8;
        putc(il & 0xff, f);
        il <<= 8;
        putc(il & 0xff, f);
        il <<= 8;
        putc(il & 0xff, f);
        il <<= 8;

        // Outsymbol length
        putc(ol & 0xff, f);
        ol <<= 8;
        putc(ol & 0xff, f);
        ol <<= 8;
        putc(ol & 0xff, f);
        ol <<= 8;
        putc(ol & 0xff, f);
        ol <<= 8;

        // Object file length
        putc(ofl & 0xff, f);
        ofl <<= 8;
        putc(ofl & 0xff, f);
        ofl <<= 8;
        putc(ofl & 0xff, f);
        ofl <<= 8;
        putc(ofl & 0xff, f);
        ofl <<= 8;


        // go through symtab and of isInsymbol > 0, add to object file
        iterator = symtabCreateIterator(symtab);
        while ((label = symtabNext(iterator, &returnData)))
        {
            Data* data = returnData;
            if (data->isInsymbol > 0)
            {
                // add to object file
                Data* addressData = symtabLookup(symtab, label);
                
                for (size_t i = 0; i < 16; i++)
                {
                    if (label[i])
                    {
                        putc(label[i], f);
                    }
                    else
                    {
                        putc(0x00, f);
                    }
                }
                
                int ad = addressData->address;

                // address
                putc(ad & 0xff, f);
                ad <<= 8;
                putc(ad & 0xff, f);
                ad <<= 8;
                putc(ad & 0xff, f);
                ad <<= 8;
                putc(ad & 0xff, f);
                ad <<= 8;
            }
        }

        // go through symtab and of isOutsymbol > 0, add to object file
        iterator = symtabCreateIterator(symtab);
        while ((label = symtabNext(iterator, &returnData)))
        {
            Data* data = returnData;
            if (data->isOutsymbol > 0)
            {
                for (int i = 0; i < data->isOutsymbol; i++)
                {
                    // add to object file
                    Data* addressData = symtabLookup(symtab, label);
                    
                    for (size_t i = 0; i < 16; i++)
                    {
                        if (label[i])
                        {
                            putc(label[i], f);
                        }
                        else
                        {
                            putc(0x00, f);
                        }
                    }
                    
                    int ad = addressData->address;

                    // address
                    putc(ad & 0xff, f);
                    ad <<= 8;
                    putc(ad & 0xff, f);
                    ad <<= 8;
                    putc(ad & 0xff, f);
                    ad <<= 8;
                    putc(ad & 0xff, f);
                    ad <<= 8;
                }
            }
        }
        // putc(0xff, f);
    }
    
    pc = 0;
    pass++;
    return errorCount;
}
