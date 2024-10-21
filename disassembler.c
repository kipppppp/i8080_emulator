#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPCODE_LENGTH 7
#define MAX_OPERANDS_LENGTH 20

// Register names
const char* reg_names[] = {"B", "C", "D", "E", "H", "L", "M", "A"};

// Function prototypes
int disassemble_i8080_opcode(unsigned char *buffer, int pc);
void print_instruction(const char *mnemonic, const char *operands);

int disassemble_i8080_opcode(unsigned char *buffer, int pc)
{
    unsigned char *code = &buffer[pc];
    int opbytes = 1;
    char mnemonic[MAX_OPCODE_LENGTH + 1] = {0};
    char operands[MAX_OPERANDS_LENGTH + 1] = {0};

    printf("%04x  %02x", pc, *code);

    switch(*code)
    {
        case 0x00: strcpy(mnemonic, "NOP"); break;
        case 0x01: sprintf(mnemonic, "LXI"); sprintf(operands, "B,#$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x02: strcpy(mnemonic, "STAX"); strcpy(operands, "B"); break;
        case 0x03: strcpy(mnemonic, "INX"); strcpy(operands, "B"); break;
        case 0x04: strcpy(mnemonic, "INR"); strcpy(operands, "B"); break;
        case 0x05: strcpy(mnemonic, "DCR"); strcpy(operands, "B"); break;
        case 0x06: strcpy(mnemonic, "MVI"); sprintf(operands, "B,#$%02x", code[1]); opbytes = 2; break;
        case 0x07: strcpy(mnemonic, "RLC"); break;
        case 0x08: strcpy(mnemonic, "NOP"); break;
        case 0x09: strcpy(mnemonic, "DAD"); strcpy(operands, "B"); break;
        case 0x0a: strcpy(mnemonic, "LDAX"); strcpy(operands, "B"); break;
        case 0x0b: strcpy(mnemonic, "DCX"); strcpy(operands, "B"); break;
        case 0x0c: strcpy(mnemonic, "INR"); strcpy(operands, "C"); break;
        case 0x0d: strcpy(mnemonic, "DCR"); strcpy(operands, "C"); break;
        case 0x0e: strcpy(mnemonic, "MVI"); sprintf(operands, "C,#$%02x", code[1]); opbytes = 2; break;
        case 0x0f: strcpy(mnemonic, "RRC"); break;
        case 0x10: strcpy(mnemonic, "NOP"); break;
        case 0x11: sprintf(mnemonic, "LXI"); sprintf(operands, "D,#$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x12: strcpy(mnemonic, "STAX"); strcpy(operands, "D"); break;
        case 0x13: strcpy(mnemonic, "INX"); strcpy(operands, "D"); break;
        case 0x14: strcpy(mnemonic, "INR"); strcpy(operands, "D"); break;
        case 0x15: strcpy(mnemonic, "DCR"); strcpy(operands, "D"); break;
        case 0x16: strcpy(mnemonic, "MVI"); sprintf(operands, "D,#$%02x", code[1]); opbytes = 2; break;
        case 0x17: strcpy(mnemonic, "RAL"); break;
        case 0x18: strcpy(mnemonic, "NOP"); break;
        case 0x19: strcpy(mnemonic, "DAD"); strcpy(operands, "D"); break;
        case 0x1a: strcpy(mnemonic, "LDAX"); strcpy(operands, "D"); break;
        case 0x1b: strcpy(mnemonic, "DCX"); strcpy(operands, "D"); break;
        case 0x1c: strcpy(mnemonic, "INR"); strcpy(operands, "E"); break;
        case 0x1d: strcpy(mnemonic, "DCR"); strcpy(operands, "E"); break;
        case 0x1e: strcpy(mnemonic, "MVI"); sprintf(operands, "E,#$%02x", code[1]); opbytes = 2; break;
        case 0x1f: strcpy(mnemonic, "RAR"); break;
        case 0x20: strcpy(mnemonic, "NOP"); break;
        case 0x21: sprintf(mnemonic, "LXI"); sprintf(operands, "H,#$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x22: sprintf(mnemonic, "SHLD"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x23: strcpy(mnemonic, "INX"); strcpy(operands, "H"); break;
        case 0x24: strcpy(mnemonic, "INR"); strcpy(operands, "H"); break;
        case 0x25: strcpy(mnemonic, "DCR"); strcpy(operands, "H"); break;
        case 0x26: strcpy(mnemonic, "MVI"); sprintf(operands, "H,#$%02x", code[1]); opbytes = 2; break;
        case 0x27: strcpy(mnemonic, "DAA"); break;
        case 0x28: strcpy(mnemonic, "NOP"); break;
        case 0x29: strcpy(mnemonic, "DAD"); strcpy(operands, "H"); break;
        case 0x2a: sprintf(mnemonic, "LHLD"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x2b: strcpy(mnemonic, "DCX"); strcpy(operands, "H"); break;
        case 0x2c: strcpy(mnemonic, "INR"); strcpy(operands, "L"); break;
        case 0x2d: strcpy(mnemonic, "DCR"); strcpy(operands, "L"); break;
        case 0x2e: strcpy(mnemonic, "MVI"); sprintf(operands, "L,#$%02x", code[1]); opbytes = 2; break;
        case 0x2f: strcpy(mnemonic, "CMA"); break;
        case 0x30: strcpy(mnemonic, "NOP"); break;
        case 0x31: sprintf(mnemonic, "LXI"); sprintf(operands, "SP,#$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x32: sprintf(mnemonic, "STA"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x33: strcpy(mnemonic, "INX"); strcpy(operands, "SP"); break;
        case 0x34: strcpy(mnemonic, "INR"); strcpy(operands, "M"); break;
        case 0x35: strcpy(mnemonic, "DCR"); strcpy(operands, "M"); break;
        case 0x36: strcpy(mnemonic, "MVI"); sprintf(operands, "M,#$%02x", code[1]); opbytes = 2; break;
        case 0x37: strcpy(mnemonic, "STC"); break;
        case 0x38: strcpy(mnemonic, "NOP"); break;
        case 0x39: strcpy(mnemonic, "DAD"); strcpy(operands, "SP"); break;
        case 0x3a: sprintf(mnemonic, "LDA"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x3b: strcpy(mnemonic, "DCX"); strcpy(operands, "SP"); break;
        case 0x3c: strcpy(mnemonic, "INR"); strcpy(operands, "A"); break;
        case 0x3d: strcpy(mnemonic, "DCR"); strcpy(operands, "A"); break;
        case 0x3e: strcpy(mnemonic, "MVI"); sprintf(operands, "A,#$%02x", code[1]); opbytes = 2; break;
        case 0x3f: strcpy(mnemonic, "CMC"); break;
        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47:
            strcpy(mnemonic, "MOV"); sprintf(operands, "B,%s", reg_names[*code & 0x07]); break;
        case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
            strcpy(mnemonic, "MOV"); sprintf(operands, "C,%s", reg_names[*code & 0x07]); break;
        case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x56: case 0x57:
            strcpy(mnemonic, "MOV"); sprintf(operands, "D,%s", reg_names[*code & 0x07]); break;
        case 0x58: case 0x59: case 0x5a: case 0x5b: case 0x5c: case 0x5d: case 0x5e: case 0x5f:
            strcpy(mnemonic, "MOV"); sprintf(operands, "E,%s", reg_names[*code & 0x07]); break;
        case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x66: case 0x67:
            strcpy(mnemonic, "MOV"); sprintf(operands, "H,%s", reg_names[*code & 0x07]); break;
        case 0x68: case 0x69: case 0x6a: case 0x6b: case 0x6c: case 0x6d: case 0x6e: case 0x6f:
            strcpy(mnemonic, "MOV"); sprintf(operands, "L,%s", reg_names[*code & 0x07]); break;
        case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: case 0x77:
            strcpy(mnemonic, "MOV"); sprintf(operands, "M,%s", reg_names[*code & 0x07]); break;
        case 0x76: strcpy(mnemonic, "HLT"); break;
        case 0x78: case 0x79: case 0x7a: case 0x7b: case 0x7c: case 0x7d: case 0x7e: case 0x7f:
            strcpy(mnemonic, "MOV"); sprintf(operands, "A,%s", reg_names[*code & 0x07]); break;
        case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87:
            strcpy(mnemonic, "ADD"); strcpy(operands, reg_names[*code & 0x07]); break;
        case 0x88: case 0x89: case 0x8a: case 0x8b: case 0x8c: case 0x8d: case 0x8e: case 0x8f:
            strcpy(mnemonic, "ADC"); strcpy(operands, reg_names[*code & 0x07]); break;
        case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95: case 0x96: case 0x97:
            strcpy(mnemonic, "SUB"); strcpy(operands, reg_names[*code & 0x07]); break;
        case 0x98: case 0x99: case 0x9a: case 0x9b: case 0x9c: case 0x9d: case 0x9e: case 0x9f:
            strcpy(mnemonic, "SBB"); strcpy(operands, reg_names[*code & 0x07]); break;
        case 0xa0: case 0xa1: case 0xa2: case 0xa3: case 0xa4: case 0xa5: case 0xa6: case 0xa7:
            strcpy(mnemonic, "ANA"); strcpy(operands, reg_names[*code & 0x07]); break;
        case 0xa8: case 0xa9: case 0xaa: case 0xab: case 0xac: case 0xad: case 0xae: case 0xaf:
            strcpy(mnemonic, "XRA"); strcpy(operands, reg_names[*code & 0x07]); break;
        case 0xb0: case 0xb1: case 0xb2: case 0xb3: case 0xb4: case 0xb5: case 0xb6: case 0xb7:
            strcpy(mnemonic, "ORA"); strcpy(operands, reg_names[*code & 0x07]); break;
        case 0xb8: case 0xb9: case 0xba: case 0xbb: case 0xbc: case 0xbd: case 0xbe: case 0xbf:
            strcpy(mnemonic, "CMP"); strcpy(operands, reg_names[*code & 0x07]); break;
        case 0xc0: strcpy(mnemonic, "RNZ"); break;
        case 0xc1: strcpy(mnemonic, "POP"); strcpy(operands, "B"); break;
        case 0xc2: sprintf(mnemonic, "JNZ"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xc3: sprintf(mnemonic, "JMP"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xc4: sprintf(mnemonic, "CNZ"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xc5: strcpy(mnemonic, "PUSH"); strcpy(operands, "B"); break;
        case 0xc6: strcpy(mnemonic, "ADI"); sprintf(operands, "#$%02x", code[1]); opbytes = 2; break;
        case 0xc7: strcpy(mnemonic, "RST"); strcpy(operands, "0"); break;
        case 0xc8: strcpy(mnemonic, "RZ"); break;
        case 0xc9: strcpy(mnemonic, "RET"); break;
        case 0xca: sprintf(mnemonic, "JZ"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xcb: strcpy(mnemonic, "NOP"); break;
        case 0xcc: sprintf(mnemonic, "CZ"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xcd: sprintf(mnemonic, "CALL"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xce: strcpy(mnemonic, "ACI"); sprintf(operands, "#$%02x", code[1]); opbytes = 2; break;
        case 0xcf: strcpy(mnemonic, "RST"); strcpy(operands, "1"); break;
        case 0xd0: strcpy(mnemonic, "RNC"); break;
        case 0xd1: strcpy(mnemonic, "POP"); strcpy(operands, "D"); break;
        case 0xd2: sprintf(mnemonic, "JNC"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xd3: strcpy(mnemonic, "OUT"); sprintf(operands, "#$%02x", code[1]); opbytes = 2; break;
        case 0xd4: sprintf(mnemonic, "CNC"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xd5: strcpy(mnemonic, "PUSH"); strcpy(operands, "D"); break;
        case 0xd6: strcpy(mnemonic, "SUI"); sprintf(operands, "#$%02x", code[1]); opbytes = 2; break;
        case 0xd7: strcpy(mnemonic, "RST"); strcpy(operands, "2"); break;
        case 0xd8: strcpy(mnemonic, "RC"); break;
        case 0xd9: strcpy(mnemonic, "NOP"); break;
        case 0xda: sprintf(mnemonic, "JC"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xdb: strcpy(mnemonic, "IN"); sprintf(operands, "#$%02x", code[1]); opbytes = 2; break;
        case 0xdc: sprintf(mnemonic, "CC"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xdd: strcpy(mnemonic, "NOP"); break;
        case 0xde: strcpy(mnemonic, "SBI"); sprintf(operands, "#$%02x", code[1]); opbytes = 2; break;
        case 0xdf: strcpy(mnemonic, "RST"); strcpy(operands, "3"); break;
        case 0xe0: strcpy(mnemonic, "RPO"); break;
        case 0xe1: strcpy(mnemonic, "POP"); strcpy(operands, "H"); break;
        case 0xe2: sprintf(mnemonic, "JPO"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xe3: strcpy(mnemonic, "XTHL"); break;
        case 0xe4: sprintf(mnemonic, "CPO"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xe5: strcpy(mnemonic, "PUSH"); strcpy(operands, "H"); break;
        case 0xe6: strcpy(mnemonic, "ANI"); sprintf(operands, "#$%02x", code[1]); opbytes = 2; break;
        case 0xe7: strcpy(mnemonic, "RST"); strcpy(operands, "4"); break;
        case 0xe8: strcpy(mnemonic, "RPE"); break;
        case 0xe9: strcpy(mnemonic, "PCHL"); break;
        case 0xea: sprintf(mnemonic, "JPE"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xeb: strcpy(mnemonic, "XCHG"); break;
        case 0xec: sprintf(mnemonic, "CPE"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xed: strcpy(mnemonic, "NOP"); break;
        case 0xee: strcpy(mnemonic, "XRI"); sprintf(operands, "#$%02x", code[1]); opbytes = 2; break;
        case 0xef: strcpy(mnemonic, "RST"); strcpy(operands, "5"); break;
        case 0xf0: strcpy(mnemonic, "RP"); break;
        case 0xf1: strcpy(mnemonic, "POP"); strcpy(operands, "PSW"); break;
        case 0xf2: sprintf(mnemonic, "JP"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xf3: strcpy(mnemonic, "DI"); break;
        case 0xf4: sprintf(mnemonic, "CP"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xf5: strcpy(mnemonic, "PUSH"); strcpy(operands, "PSW"); break;
        case 0xf6: strcpy(mnemonic, "ORI"); sprintf(operands, "#$%02x", code[1]); opbytes = 2; break;
        case 0xf7: strcpy(mnemonic, "RST"); strcpy(operands, "6"); break;
        case 0xf8: strcpy(mnemonic, "RM"); break;
        case 0xf9: strcpy(mnemonic, "SPHL"); break;
        case 0xfa: sprintf(mnemonic, "JM"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xfb: strcpy(mnemonic, "EI"); break;
        case 0xfc: sprintf(mnemonic, "CM"); sprintf(operands, "$%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xfd: strcpy(mnemonic, "NOP"); break;
        case 0xfe: strcpy(mnemonic, "CPI"); sprintf(operands, "#$%02x", code[1]); opbytes = 2; break;
        case 0xff: strcpy(mnemonic, "RST"); strcpy(operands, "7"); break;
    }

    // Print the remaining bytes of the instruction
    for (int i = 1; i < opbytes; i++) {
        printf(" %02x", code[i]);
    }
    // Pad with spaces for alignment
    for (int i = opbytes; i < 3; i++) {
        printf("   ");
    }

    print_instruction(mnemonic, operands);
    return opbytes;
}

void print_instruction(const char *mnemonic, const char *operands)
{
    printf("  %-7s", mnemonic);
    if (strlen(operands) > 0) {
        printf(" %s", operands);
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <filename> [start_address] [num_instructions]\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if(f == NULL)
    {
        printf("Error: Could not open %s\n", argv[1]);
        return 1;
    }

    fseek(f, 0L, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);
    
    unsigned char *buffer = malloc(fsize);
    if (buffer == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(f);
        return 1;
    }

    size_t read_size = fread(buffer, 1, fsize, f);
    fclose(f);

    if (read_size != fsize) {
        printf("Error: File read failed\n");
        free(buffer);
        return 1;
    }

    int pc = 0;
    int num_instructions = fsize;

    if (argc > 2) {
        pc = (int)strtol(argv[2], NULL, 0);
    }

    if (argc > 3) {
        num_instructions = (int)strtol(argv[3], NULL, 0);
    }

    int instructions_processed = 0;
    while (pc < fsize && instructions_processed < num_instructions) {
        pc += disassemble_i8080_opcode(buffer, pc);
        instructions_processed++;
    }

    free(buffer);
    return 0;
}