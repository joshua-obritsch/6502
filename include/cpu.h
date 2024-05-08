#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#define MEMORY_SIZE  65536
#define STACK_OFFSET 256

typedef int8_t   i8;
typedef uint8_t  u8;
typedef uint16_t u16;

typedef struct Cpu {
    // Registers
    u16 pc; // Program counter    (16 bit)
    u8  ac; // Accumulator         (8 bit)
    u8   x; // X register          (8 bit)
    u8   y; // Y register          (8 bit)
    u8  sp; // Stack pointer       (8 bit)

    union {
        u8 sr; // Status register  (8 bit)

        // Flags [NV-BDIZC]
        struct {
            u8 c : 1; // Carry     (bit 0)
            u8 z : 1; // Zero      (bit 1)
            u8 i : 1; // Interrupt (bit 2)
            u8 d : 1; // Decimal   (bit 3)
            u8 b : 1; // Break     (bit 4)
            u8   : 1; // Ignored   (bit 5)
            u8 v : 1; // Overflow  (bit 6)
            u8 n : 1; // Negative  (bit 7)
        };
    };

    // Memory
    u8 memory[MEMORY_SIZE];
} Cpu;

// Returns a byte from memory given an address without incrementing the PC.
static inline u8 peekByte(Cpu* cpu, u16 address);

// Returns a word from memory given an address without incrementing the PC.
static inline u16 peekWord(Cpu* cpu, u16 address);

// Returns the next byte from memory and increments the PC.
static inline u8 fetchByte(Cpu* cpu);

// Returns the next word from memory and increments the PC.
static inline u16 fetchWord(Cpu* cpu);

// Returns a byte from zero-page memory.
static inline u8 fetchZeropage(Cpu* cpu);

// Returns a byte from zero-page memory where the address is offset by X.
static inline u8 fetchZeropageX(Cpu* cpu);

// Returns a byte from zero-page memory where the address is offset by Y.
static inline u8 fetchZeropageY(Cpu* cpu);

// Returns a byte from memory.
static inline u8 fetchAbsolute(Cpu* cpu);

// Returns a byte from memory where the address is offset by X.
static inline u8 fetchAbsoluteX(Cpu* cpu);

// Returns a byte from memory where the address is offset by Y.
static inline u8 fetchAbsoluteY(Cpu* cpu);

// Returns a word from memory via an indirect address.
static inline u16 fetchIndirect(Cpu* cpu);

// Returns a byte from memory via an indirect address offset by X.
static inline u8 fetchIndirectX(Cpu* cpu);

// Returns a byte from memory via an indirect address offset by Y.
static inline u8 fetchIndirectY(Cpu* cpu);

// Returns a word from memory offsetting the PC.
static inline u16 fetchRelative(Cpu* cpu);

// Whether the page boundary was crossed by absolute-X addressing.
static inline int isPageBoundaryCrossedByAbsoluteX(Cpu* cpu);

// Whether the page boundary was crossed by absolute-Y addressing.
static inline int isPageBoundaryCrossedByAbsoluteY(Cpu* cpu);

// Whether the page boundary was crossed by indirect-Y addressing.
static inline int isPageBoundaryCrossedByIndirectY(Cpu* cpu);

// Sets the non-positive flags: negative and zero (NZ).
void setNonpositiveFlags(Cpu* cpu, u8 value);

// Sets the arithmetic flags: negative, zero, carry, and overflow (NZCV).
void setArithmeticFlags(Cpu* cpu);

/*
// Sets the comparable flags: negative (N), zero (Z), and carry (C).
void setComparableFlags(Cpu* cpu, i8 a, u8 b) {
    cpu->n = (value & 0b10000000) > 0;
    cpu->z = value == 0;
}
*/

int executeInstruction(Cpu* cpu);

void resetCpu(Cpu* cpu);

#endif // CPU_H
