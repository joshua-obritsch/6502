#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "instructions.h"

// Returns a byte from memory given an address without incrementing the PC.
static inline u8 peekByte(Cpu* cpu, u16 address) {
    return cpu->memory[address];
}

// Returns a word from memory given an address without incrementing the PC.
static inline u16 peekWord(Cpu* cpu, u16 address) {
    return cpu->memory[address] | cpu->memory[address + 1] << 8;
}

// Returns the next byte from memory and increments the PC.
static inline u8 fetchByte(Cpu* cpu) {
    return cpu->memory[cpu->pc++];
}

// Returns the next word from memory and increments the PC.
static inline u16 fetchWord(Cpu* cpu) {
    return fetchByte(cpu) | fetchByte(cpu) << 8;
}

// Returns a byte from zero-page memory.
static inline u8 fetchZeropage(Cpu* cpu) {
    return cpu->memory[fetchByte(cpu)];
}

// Returns a byte from zero-page memory where the address is offset by X.
static inline u8 fetchZeropageX(Cpu* cpu) {
    return cpu->memory[(u8)(fetchByte(cpu) + cpu->x)];
}

// Returns a byte from zero-page memory where the address is offset by Y.
static inline u8 fetchZeropageY(Cpu* cpu) {
    return cpu->memory[(u8)(fetchByte(cpu) + cpu->y)];
}

// Returns a byte from memory.
static inline u8 fetchAbsolute(Cpu* cpu) {
    return cpu->memory[fetchWord(cpu)];
}

// Returns a byte from memory where the address is offset by X.
static inline u8 fetchAbsoluteX(Cpu* cpu) {
    return cpu->memory[fetchWord(cpu) + cpu->x];
}

// Returns a byte from memory where the address is offset by Y.
static inline u8 fetchAbsoluteY(Cpu* cpu) {
    return cpu->memory[fetchWord(cpu) + cpu->y];
}

// Returns a word from memory via an indirect address.
static inline u16 fetchIndirect(Cpu* cpu) {
    return peekWord(cpu, fetchWord(cpu));
}

// Returns a byte from memory via an indirect address offset by X.
static inline u8 fetchIndirectX(Cpu* cpu) {
    return cpu->memory[peekWord(cpu, (u8)(fetchByte(cpu) + cpu->x))];
}

// Returns a byte from memory via an indirect address offset by Y.
static inline u8 fetchIndirectY(Cpu* cpu) {
    return cpu->memory[peekWord(cpu, fetchByte(cpu)) + cpu->y];
}

// Returns a word from memory offsetting the PC.
static inline u16 fetchRelative(Cpu* cpu) {
    return cpu->pc + (i8)cpu->memory[cpu->pc];
}

// Sets a byte in zero-page memory.
static inline void setZeropage(Cpu* cpu, u8 byte) {
    cpu->memory[fetchByte(cpu)] = byte;
}

// Sets a byte in zero-page memory where the address is offset by X.
static inline void setZeropageX(Cpu* cpu, u8 byte) {
    cpu->memory[(u8)(fetchByte(cpu) + cpu->x)] = byte;
}

// Sets a byte in zero-page memory where the address is offset by Y.
static inline void setZeropageY(Cpu* cpu, u8 byte) {
    cpu->memory[(u8)(fetchByte(cpu) + cpu->y)] = byte;
}

// Sets a byte in memory.
static inline void setAbsolute(Cpu* cpu, u8 byte) {
    cpu->memory[fetchWord(cpu)] = byte;
}

// Sets a byte in memory where the address is offset by X.
static inline void setAbsoluteX(Cpu* cpu, u8 byte) {
    cpu->memory[fetchWord(cpu) + cpu->x] = byte;
}

// Sets a byte in memory where the address is offset by Y.
static inline void setAbsoluteY(Cpu* cpu, u8 byte) {
    cpu->memory[fetchWord(cpu) + cpu->y] = byte;
}

// Sets a byte in memory via an indirect address offset by X.
static inline void setIndirectX(Cpu* cpu, u8 byte) {
    cpu->memory[peekWord(cpu, (u8)(fetchByte(cpu) + cpu->x))] = byte;
}

// Sets a byte in memory via an indirect address offset by Y.
static inline void setIndirectY(Cpu* cpu, u8 byte) {
    cpu->memory[peekWord(cpu, fetchByte(cpu)) + cpu->y] = byte;
}

// Pushes a byte onto the stack.
static inline void pushByte(Cpu* cpu, u8 byte) {
    cpu->memory[STACK_OFFSET + cpu->sp--] = byte;
}

// Pushes a word onto the stack.
static inline void pushWord(Cpu* cpu, u16 word) {
    pushByte(cpu, word); pushByte(cpu, word >> 8);
}

// Pops a byte off the stack.
static inline u8 popByte(Cpu* cpu) {
    return cpu->memory[STACK_OFFSET + ++cpu->sp];
}

// Pops a word off the stack.
static inline u16 popWord(Cpu* cpu) {
    return popByte(cpu) << 8 | popByte(cpu);
}

// Whether the page boundary was crossed by absolute-X addressing.
static inline int isPageBoundaryCrossedByAbsoluteX(Cpu* cpu) {
    return cpu->memory[cpu->pc - 2] + cpu->x > 0xFF;
}

// Whether the page boundary was crossed by absolute-Y addressing.
static inline int isPageBoundaryCrossedByAbsoluteY(Cpu* cpu) {
    return cpu->memory[cpu->pc - 2] + cpu->y > 0xFF;
}

// Whether the page boundary was crossed by indirect-Y addressing.
static inline int isPageBoundaryCrossedByIndirectY(Cpu* cpu) {
    return peekByte(cpu, cpu->memory[cpu->pc - 1]) + cpu->y > 0xFF;
}

// Sets the non-positive flags: negative and zero (NZ).
void setNonpositiveFlags(Cpu* cpu, u8 value) {
    cpu->n = !!(value & 0x80u);
    cpu->z = !value;
}

// Sets the arithmetic flags: negative, zero, carry, and overflow (NZCV).
void setArithmeticFlags(Cpu* cpu) {
    cpu->n = !!(cpu->a & 0x80u);
    cpu->z = !cpu->a;
}

void setOverflowFlag(Cpu* cpu, u8 a, u8 b, u8 c) {
    cpu->v = (a ^ c) & (b ^ c) & 0x80u;
}

/*
// Sets the comparable flags: negative (N), zero (Z), and carry (C).
void setComparableFlags(Cpu* cpu, i8 a, u8 b) {
    cpu->n = (value & 0b10000000) > 0;
    cpu->z = value == 0;
}
*/

int executeInstruction(Cpu* cpu) {
    u8 opcode = fetchByte(cpu);

    switch (opcode) {
        // ADC
        case ADC_IMM:
            cpu->a += (i8)fetchByte(cpu) + cpu->c;
            setArithmeticFlags(cpu);
            return 2;
        case ADC_ZPG:
            cpu->a += fetchZeropage(cpu);
            return 3;
        case ADC_ZPGX:
            cpu->a += fetchZeropageX(cpu);
            return 4;
        case ADC_ABS:
            cpu->a += fetchAbsolute(cpu);
            return 4;
        case ADC_ABSX:
            cpu->a += fetchAbsoluteX(cpu);
            return isPageBoundaryCrossedByAbsoluteX(cpu) ? 5 : 4;
        case ADC_ABSY:
            cpu->a += fetchAbsoluteY(cpu);
            return isPageBoundaryCrossedByAbsoluteY(cpu) ? 5 : 4;
        case ADC_INDX:
            cpu->a += fetchIndirectX(cpu);
            return 6;
        case ADC_INDY:
            cpu->a += fetchIndirectY(cpu);
            return isPageBoundaryCrossedByIndirectY(cpu) ? 6 : 5;

        // CLC
        case CLC_IMPL:
            cpu->c = 0;
            return 2;

        // CLD
        case CLD_IMPL:
            cpu->d = 0;
            return 2;

        // CLI
        case CLI_IMPL:
            cpu->i = 0;
            return 2;

        // CLV
        case CLV_IMPL:
            cpu->v = 0;
            return 2;

        // JMP
        case JMP_ABS:
            cpu->pc = peekWord(cpu, cpu->pc);
            return 3;
        case JMP_IND:
            cpu->pc = peekWord(cpu, peekWord(cpu, cpu->pc));
            return 5;

        // JSR
        case JSR_ABS:
            pushWord(cpu, cpu->pc + 1);
            cpu->pc = peekWord(cpu, cpu->pc);
            return 6;

        // LDA
        case LDA_IMM:
            cpu->a = fetchByte(cpu);
            setNonpositiveFlags(cpu, cpu->a);
            return 2;
        case LDA_ZPG:
            cpu->a = fetchZeropage(cpu);
            setNonpositiveFlags(cpu, cpu->a);
            return 3;
        case LDA_ZPGX:
            cpu->a = fetchZeropageX(cpu);
            setNonpositiveFlags(cpu, cpu->a);
            return 4;
        case LDA_ABS:
            cpu->a = fetchAbsolute(cpu);
            setNonpositiveFlags(cpu, cpu->a);
            return 4;
        case LDA_ABSX:
            cpu->a = fetchAbsoluteX(cpu);
            setNonpositiveFlags(cpu, cpu->a);
            return isPageBoundaryCrossedByAbsoluteX(cpu) ? 5 : 4;
        case LDA_ABSY:
            cpu->a = fetchAbsoluteY(cpu);
            setNonpositiveFlags(cpu, cpu->a);
            return isPageBoundaryCrossedByAbsoluteY(cpu) ? 5 : 4;
        case LDA_INDX:
            cpu->a = fetchIndirectX(cpu);
            setNonpositiveFlags(cpu, cpu->a);
            return 6;
        case LDA_INDY:
            cpu->a = fetchIndirectY(cpu);
            setNonpositiveFlags(cpu, cpu->a);
            return isPageBoundaryCrossedByIndirectY(cpu) ? 6 : 5;

        // LDX
        case LDX_IMM:
            cpu->x = fetchByte(cpu);
            setNonpositiveFlags(cpu, cpu->x);
            return 2;
        case LDX_ZPG:
            cpu->x = fetchZeropage(cpu);
            setNonpositiveFlags(cpu, cpu->x);
            return 3;
        case LDX_ZPGY:
            cpu->x = fetchZeropageY(cpu);
            setNonpositiveFlags(cpu, cpu->x);
            return 4;
        case LDX_ABS:
            cpu->x = fetchAbsolute(cpu);
            setNonpositiveFlags(cpu, cpu->x);
            return 4;
        case LDX_ABSY:
            cpu->x = fetchAbsoluteY(cpu);
            setNonpositiveFlags(cpu, cpu->x);
            return isPageBoundaryCrossedByAbsoluteY(cpu) ? 5 : 4;

        // LDY
        case LDY_IMM:
            cpu->y = fetchByte(cpu);
            setNonpositiveFlags(cpu, cpu->y);
            return 2;
        case LDY_ZPG:
            cpu->y = fetchZeropage(cpu);
            setNonpositiveFlags(cpu, cpu->y);
            return 3;
        case LDY_ZPGX:
            cpu->y = fetchZeropageX(cpu);
            setNonpositiveFlags(cpu, cpu->y);
            return 4;
        case LDY_ABS:
            cpu->y = fetchAbsolute(cpu);
            setNonpositiveFlags(cpu, cpu->y);
            return 4;
        case LDY_ABSX:
            cpu->y = fetchAbsoluteX(cpu);
            setNonpositiveFlags(cpu, cpu->y);
            return isPageBoundaryCrossedByAbsoluteX(cpu) ? 5 : 4;

        // PHA
        case PHA_IMPL:
            pushByte(cpu, cpu->a);
            return 3;

        // RTS
        case RTS_IMPL:
            cpu->pc = popWord(cpu) + 1;
            return 6;

        // SEC
        case SEC_IMPL:
            cpu->c = 1;
            return 2;

        // SED
        case SED_IMPL:
            cpu->d = 1;
            return 2;

        // SEI
        case SEI_IMPL:
            cpu->i = 1;
            return 2;

        // STA
        case STA_ZPG:
            setZeropage(cpu, cpu->a);
            return 3;
        case STA_ZPGX:
            setZeropageX(cpu, cpu->a);
            return 4;
        case STA_ABS:
            setAbsolute(cpu, cpu->a);
            return 4;
        case STA_ABSX:
            setAbsoluteX(cpu, cpu->a);
            return 5;
        case STA_ABSY:
            setAbsoluteY(cpu, cpu->a);
            return 5;
        case STA_INDX:
            setIndirectX(cpu, cpu->a);
            return 6;
        case STA_INDY:
            setIndirectY(cpu, cpu->a);
            return 6;

        // STX
        case STX_ZPG:
            setZeropage(cpu, cpu->x);
            return 3;
        case STX_ZPGY:
            setZeropageY(cpu, cpu->x);
            return 4;
        case STX_ABS:
            setAbsolute(cpu, cpu->x);
            return 4;

        // STY
        case STY_ZPG:
            setZeropage(cpu, cpu->y);
            return 3;
        case STY_ZPGX:
            setZeropageX(cpu, cpu->y);
            return 4;
        case STY_ABS:
            setAbsolute(cpu, cpu->y);
            return 4;

        // TAX
        case TAX_IMPL:
            cpu->x = cpu->a;
            setNonpositiveFlags(cpu, cpu->x);
            return 2;

        // TAY
        case TAY_IMPL:
            cpu->y = cpu->a;
            setNonpositiveFlags(cpu, cpu->y);
            return 2;

        // TSX
        case TSX_IMPL:
            cpu->x = popByte(cpu);
            setNonpositiveFlags(cpu, cpu->x);
            return 2;

        // TXA
        case TXA_IMPL:
            cpu->a = cpu->x;
            setNonpositiveFlags(cpu, cpu->a);
            return 2;

        // TXS
        case TXS_IMPL:
            cpu->sp = cpu->x;
            return 2;

        // TYA
        case TYA_IMPL:
            cpu->a = cpu->y;
            setNonpositiveFlags(cpu, cpu->a);
            return 2;

        default:
            printf("Unexpected opcode: 0x%02x\n", opcode);
            exit(0);
    }
    /*setNegativeFlag(cpu, cpu->a); setZeroFlag(cpu, cpu->a);*/
}

void resetCpu(Cpu* cpu) {
    cpu->pc = 0xFFFC;
    cpu->a  = 0;
    cpu->x  = 0;
    cpu->y  = 0;
    cpu->sr = 0x04;
    cpu->sp = 0x00;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        cpu->memory[i] = 0;
    }
}

