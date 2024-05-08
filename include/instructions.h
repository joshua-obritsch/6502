#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

//      ADC    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             +++--+    ------------   ------------   ------   -----   ------
#define ADC_IMM  0x69 // ADC #oper      immediate      69       2       2
#define ADC_ZPG  0x65 // ADC oper       zeropage       65       2       3
#define ADC_ZPGX 0x75 // ADC oper,X     zeropage,X     75       2       4
#define ADC_ABS  0x6D // ADC oper       absolute       6D       3       4
#define ADC_ABSX 0x7D // ADC oper,X     absolute,X     7D       3       4*
#define ADC_ABSY 0x79 // ADC oper,Y     absolute,Y     79       3       4*
#define ADC_INDX 0x61 // ADC (oper,X)   (indirect,X)   61       2       6
#define ADC_INDY 0x71 // ADC (oper),Y   (indirect),Y   71       2       5*

//      AND    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define AND_IMM  0x29 // AND #oper      immediate      29       2       2
#define AND_ZPG  0x25 // AND oper       zeropage       25       2       3
#define AND_ZPGX 0x35 // AND oper,X     zeropage,X     35       2       4
#define AND_ABS  0x2D // AND oper       absolute       2D       3       4
#define AND_ABSX 0x3D // AND oper,X     absolute,X     3D       3       4*
#define AND_ABSY 0x39 // AND oper,Y     absolute,Y     39       3       4*
#define AND_INDX 0x21 // AND (oper,X)   (indirect,X)   21       2       6
#define AND_INDY 0x31 // AND (oper),Y   (indirect),Y   31       2       5*

//      ASL    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             +++---    ------------   ------------   ------   -----   ------
#define ASL_ACC  0x0A // ASL A          accumulator    0A       1       2
#define ASL_ZPG  0x06 // ASL oper       zeropage       06       2       5
#define ASL_ZPGX 0x16 // ASL oper,X     zeropage,X     16       2       6
#define ASL_ABS  0x0E // ASL oper       absolute       0E       3       6
#define ASL_ABSX 0x1E // ASL oper,X     absolute,X     1E       3       7

//      BCC    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define BCC_REL  0x90 // BCC oper       relative       90       2       2**

//      BCS    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define BCS_REL  0xB0 // BCS oper       relative       B0       2       2**

//      BEQ    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define BEQ_REL  0xF0 // BEQ oper       relative       F0       2       2**

//      BIT    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++---+    ------------   ------------   ------   -----   ------
#define BIT_ZPG  0x24 // BIT oper       zeropage       24       2       3
#define BIT_ABS  0x2C // BIT oper       absolute       2C       3       4

//      BMI    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define BMI_REL  0x30 // BMI oper       relative       30       2       2**

//      BNE    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define BNE_REL  0xD0 // BNE oper       relative       D0       2       2**

//      BPL    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define BPL_REL  0x10 // BPL oper       relative       10       2       2**

//      BRK    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define BRK_IMPL 0x00 // BRK            implied        00       1       7

//      BVC    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define BVC_REL  0x50 // BVC oper       relative       50       2       2**

//      BVS    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define BVS_REL  0x70 // BVS oper       relative       70       2       2**

//      CLC    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             --+---    ------------   ------------   ------   -----   ------
#define CLC_IMPL 0x18 // CLC            implied        18       1       2

//      CLD    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ----+-    ------------   ------------   ------   -----   ------
#define CLD_IMPL 0xD8 // CLD            implied        D8       1       2

//      CLI    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ---+--    ------------   ------------   ------   -----   ------
#define CLI_IMPL 0x58 // CLI            implied        58       1       2

//      CLV    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             -----+    ------------   ------------   ------   -----   ------
#define CLV_IMPL 0xB8 // CLV            implied        B8       1       2

//      CMP    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             +++---    ------------   ------------   ------   -----   ------
#define CMP_IMM  0xC9 // CMP #oper      immediate      C9       2       2
#define CMP_ZPG  0xC5 // CMP oper       zeropage       C5       2       3
#define CMP_ZPGX 0xD5 // CMP oper,X     zeropage,X     D5       2       4
#define CMP_ABS  0xCD // CMP oper       absolute       CD       3       4
#define CMP_ABSX 0xDD // CMP oper,X     absolute,X     DD       3       4*
#define CMP_ABSY 0xD9 // CMP oper,Y     absolute,Y     D9       3       4*
#define CMP_INDX 0xC1 // CMP (oper,X)   (indirect,X)   C1       2       6
#define CMP_INDY 0xD1 // CMP (oper),Y   (indirect),Y   D1       2       5*

//      CPX    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             +++---    ------------   ------------   ------   -----   ------
#define CPX_IMM  0xE0 // CPX #oper      immediate      E0       2       2
#define CPX_ZPG  0xE4 // CPX oper       zeropage       E4       2       3
#define CPX_ABS  0xEC // CPX oper       absolute       EC       3       4

//      CPY    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             +++---    ------------   ------------   ------   -----   ------
#define CPY_IMM  0xC0 // CPY #oper      immediate      C0       2       2
#define CPY_ZPG  0xC4 // CPY oper       zeropage       C4       2       3
#define CPY_ABS  0xCC // CPY oper       absolute       CC       3       4

//      DEC    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define DEC_ZPG  0xC6 // DEC oper       zeropage       C6       2       5
#define DEC_ZPGX 0xD6 // DEC oper,X     zeropage,X     D6       2       6
#define DEC_ABS  0xCE // DEC oper       absolute       CE       3       6
#define DEC_ABSX 0xDE // DEC oper,X     absolute,X     DE       3       7

//      DEX    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define DEX_IMPL 0xCA // DEX            implied        CA       1       2

//      DEY    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define DEY_IMPL 0x88 // DEY            implied        88       1       2

//      EOR    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define EOR_IMM  0x49 // EOR #oper      immediate      49       2       2
#define EOR_ZPG  0x45 // EOR oper       zeropage       45       2       3
#define EOR_ZPGX 0x55 // EOR oper,X     zeropage,X     55       2       4
#define EOR_ABS  0x4D // EOR oper       absolute       4D       3       4
#define EOR_ABSX 0x5D // EOR oper,X     absolute,X     5D       3       4*
#define EOR_ABSY 0x59 // EOR oper,Y     absolute,Y     59       3       4*
#define EOR_INDX 0x41 // EOR (oper,X)   (indirect,X)   41       2       6
#define EOR_INDY 0x51 // EOR (oper),Y   (indirect),Y   51       2       5*

//      INC    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define INC_ZPG  0xE6 // INC oper       zeropage       E6       2       5
#define INC_ZPGX 0xF6 // INC oper,X     zeropage,X     F6       2       6
#define INC_ABS  0xEE // INC oper       absolute       EE       3       6
#define INC_ABSX 0xFE // INC oper,X     absolute,X     FE       3       7

//      INX    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define INX_IMPL 0xE8 // INX            implied        E8       1       2

//      INY    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define INY_IMPL 0xC8 // INY            implied        C8       1       2

//      JMP    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define JMP_ABS  0x4C // JMP oper       absolute       4C       3       3
#define JMP_IND  0x6C // JMP (oper)     indirect       6C       3       5

//      JSR    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define JSR_ABS  0x20 // JSR oper       absolute       20       3       6

//      LDA    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define LDA_IMM  0xA9 // LDA #oper      immediate      A9       2       2
#define LDA_ZPG  0xA5 // LDA oper       zeropage       A5       2       3
#define LDA_ZPGX 0xB5 // LDA oper,X     zeropage,X     B5       2       4
#define LDA_ABS  0xAD // LDA oper       absolute       AD       3       4
#define LDA_ABSX 0xBD // LDA oper,X     absolute,X     BD       3       4*
#define LDA_ABSY 0xB9 // LDA oper,Y     absolute,Y     B9       3       4*
#define LDA_INDX 0xA1 // LDA (oper,X)   (indirect,X)   A1       2       6
#define LDA_INDY 0xB1 // LDA (oper),Y   (indirect),Y   B1       2       5*

//      LDX    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define LDX_IMM  0xA2 // LDX #oper      immediate      A2       2       2
#define LDX_ZPG  0xA6 // LDX oper       zeropage       A6       2       3
#define LDX_ZPGY 0xB6 // LDX oper,Y     zeropage,Y     B6       2       4
#define LDX_ABS  0xAE // LDX oper       absolute       AE       3       4
#define LDX_ABSY 0xBE // LDX oper,Y     absolute,Y     BE       3       4*

//      LDY    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define LDY_IMM  0xA0 // LDY #oper      immediate      A0       2       2
#define LDY_ZPG  0xA4 // LDY oper       zeropage       A4       2       3
#define LDY_ZPGX 0xB4 // LDY oper,X     zeropage,X     B4       2       4
#define LDY_ABS  0xAC // LDY oper       absolute       AC       3       4
#define LDY_ABSX 0xBC // LDY oper,X     absolute,X     BC       3       4*

//      LSR    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             +++---    ------------   ------------   ------   -----   ------
#define LSR_ACC  0x4A // LSR A          accumulator    4A       1       2
#define LSR_ZPG  0x46 // LSR oper       zeropage       46       2       5
#define LSR_ZPGX 0x56 // LSR oper,X     zeropage,X     56       2       6
#define LSR_ABS  0x4E // LSR oper       absolute       4E       3       6
#define LSR_ABSX 0x5E // LSR oper,X     absolute,X     5E       3       7

//      NOP    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define NOP_IMPL 0xEA // NOP            implied        EA       1       2

//      ORA    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define ORA_IMM  0x09 // ORA #oper      immediate      09       2       2
#define ORA_ZPG  0x05 // ORA oper       zeropage       05       2       3
#define ORA_ZPGX 0x15 // ORA oper,X     zeropage,X     15       2       4
#define ORA_ABS  0x0D // ORA oper       absolute       0D       3       4
#define ORA_ABSX 0x1D // ORA oper,X     absolute,X     1D       3       4*
#define ORA_ABSY 0x19 // ORA oper,Y     absolute,Y     19       3       4*
#define ORA_INDX 0x01 // ORA (oper,X)   (indirect,X)   01       2       6
#define ORA_INDY 0x11 // ORA (oper),Y   (indirect),Y   11       2       5*

//      PHA    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define PHA_IMPL 0x48 // PHA            implied        48       1       3

//      PHP    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define PHP_IMPL 0x08 // PHP            implied        08       1       3

//      PLA    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define PLA_IMPL 0x68 // PLA            implied        68       1       4

//      PLP    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++++++    ------------   ------------   ------   -----   ------
#define PLP_IMPL 0x28 // PLP            implied        28       1       4

//      ROL    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             +++---    ------------   ------------   ------   -----   ------
#define ROL_ACC  0x2A // ROL A          accumulator    2A       1       2
#define ROL_ZPG  0x26 // ROL oper       zeropage       26       2       5
#define ROL_ZPGX 0x36 // ROL oper,X     zeropage,X     36       2       6
#define ROL_ABS  0x2E // ROL oper       absolute       2E       3       6
#define ROL_ABSX 0x3E // ROL oper,X     absolute,X     3E       3       7

//      ROR    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             +++---    ------------   ------------   ------   -----   ------
#define ROR_ACC  0x6A // ROR A          accumulator    6A       1       2
#define ROR_ZPG  0x66 // ROR oper       zeropage       66       2       5
#define ROR_ZPGX 0x76 // ROR oper,X     zeropage,X     76       2       6
#define ROR_ABS  0x6E // ROR oper       absolute       6E       3       6
#define ROR_ABSX 0x7E // ROR oper,X     absolute,X     7E       3       7

//      RTI    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++++++    ------------   ------------   ------   -----   ------
#define RTI_IMPL 0x40 // RTI            implied        40       1       6

//      RTS    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define RTS_IMPL 0x60 // RTS            implied        60       1       6

//      SBC    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             +++--+    ------------   ------------   ------   -----   ------
#define SBC_IMM  0xE9 // SBC #oper      immediate      E9       2       2
#define SBC_ZPG  0xE5 // SBC oper       zeropage       E5       2       3
#define SBC_ZPGX 0xF5 // SBC oper,X     zeropage,X     F5       2       4
#define SBC_ABS  0xED // SBC oper       absolute       ED       3       4
#define SBC_ABSX 0xFD // SBC oper,X     absolute,X     FD       3       4*
#define SBC_ABSY 0xF9 // SBC oper,Y     absolute,Y     F9       3       4*
#define SBC_INDX 0xE1 // SBC (oper,X)   (indirect,X)   E1       2       6
#define SBC_INDY 0xF1 // SBC (oper),Y   (indirect),Y   F1       2       5*

//      SEC    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             --+---    ------------   ------------   ------   -----   ------
#define SEC_IMPL 0x38 // SEC            implied        38       1       2

//      SED    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ----+-    ------------   ------------   ------   -----   ------
#define SED_IMPL 0xF8 // SED            implied        F8       1       2

//      SEI    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ---+--    ------------   ------------   ------   -----   ------
#define SEI_IMPL 0x78 // SEI            implied        78       1       2

//      STA    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define STA_ZPG  0x85 // STA oper       zeropage       85       2       3
#define STA_ZPGX 0x95 // STA oper,X     zeropage,X     95       2       4
#define STA_ABS  0x8D // STA oper       absolute       8D       3       4
#define STA_ABSX 0x9D // STA oper,X     absolute,X     9D       3       5
#define STA_ABSY 0x99 // STA oper,Y     absolute,Y     99       3       5
#define STA_INDX 0x81 // STA (oper,X)   (indirect,X)   81       2       6
#define STA_INDY 0x91 // STA (oper),Y   (indirect),Y   91       2       6

//      STX    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define STX_ZPG  0x86 // STX oper       zeropage       86       2       3
#define STX_ZPGY 0x96 // STX oper,Y     zeropage,Y     96       2       4
#define STX_ABS  0x8E // STX oper       absolute       8E       3       4

//      STY    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define STY_ZPG  0x84 // STY oper       zeropage       84       2       3
#define STY_ZPGX 0x94 // STY oper,X     zeropage,X     94       2       4
#define STY_ABS  0x8C // STY oper       absolute       8C       3       4

//      TAX    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define TAX_IMPL 0xAA // TAX            implied        AA       1       2

//      TAY    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define TAY_IMPL 0xAB // TAY            implied        AB       1       2

//      TSX    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define TSX_IMPL 0xBA // TSX            implied        BA       1       2

//      TXA    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define TXA_IMPL 0x8A // TXA            implied        8A       1       2

//      TXS    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ------    ------------   ------------   ------   -----   ------
#define TXS_IMPL 0x9A // TXS            implied        9A       1       2

//      TYA    NZCIDV    Syntax         Addressing     Opcode   Bytes   Cycles
//             ++----    ------------   ------------   ------   -----   ------
#define TYA_IMPL 0x98 // TYA            implied        98       1       2

#endif // INSTRUCTIONS_H
