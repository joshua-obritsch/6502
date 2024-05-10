#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "test.h"

Cpu cpu;
int cycles                 = 0;
int localExpectCount       = 0;
int localExpectPassedCount = 0;
int localTestCount         = 0;
int localTestPassedCount   = 0;
int totalTestCount         = 0;
int totalTestPassedCount   = 0;

int testSuite = 1;
char* testName;

int main(int argc, char** argv) {
    if (argc > 1) {
        int count = argc - 1;

        while (count > 0) {
            switch (argv[count][0]) {
                case '-':
                    if (strlen(argv[count]) < 2) {
                        printf("Syntax error.\n");
                        exit(EXIT_FAILURE);
                    }

                    switch (argv[count][1]) {
                        case 't':
                            testSuite = 0;
                            break;
                    }

                    break;
                default:
                    if (testName != NULL) {
                        printf("Syntax error.\n");
                        exit(EXIT_FAILURE);
                    }

                    testName = argv[count];

                    break;
            }

            count--;
        }
    }

    ADC();
    JMP();
    JSR();
    LDA();
    LDX();
    LDY();
    PHA();
    RTS();
    STA();
    STX();
    STY();
    TAX();
    TAY();
    TSX();
    TXA();
    TXS();
    TYA();

    printf("╔═[RESULTS]"); \
    for (int i = 0; i < 68; i++) {
        printf("═");
    }
    printf("╗\n");

    if (totalTestCount == 0) {
        printf("║ ALL TESTS SKIPPED.");
        for (int i = 0; i < 60; i++) {
            printf(" ");
        }
        printf("║\n");
    } else if (totalTestCount == totalTestPassedCount) {
        printf("║ \033[32mALL TESTS PASSED.\033[0m");
        for (int i = 0; i < 60; i++) {
            printf(" ");
        }
        printf("║\n");
    } else {
        printf("║ DONE: %d", totalTestCount);
        for (int i = 0; i < 71 - intlen(localTestCount); i++) {
            printf(" ");
        }
        printf("║\n");

        int totalTestFailedCount = totalTestCount - totalTestPassedCount;
        printf("║ \033[31mFAIL\033[0m: %d", totalTestFailedCount);
        for (int i = 0; i < 71 - intlen(totalTestFailedCount); i++) {
            printf(" ");
        }
        printf("║\n");

        printf("║ \033[32mPASS\033[0m: %d", totalTestPassedCount);
        for (int i = 0; i < 71 - intlen(totalTestPassedCount); i++) {
            printf(" ");
        }
        printf("║\n");
    }

    BOTTOM;

    printf("\n");

    return 0;
}

/* NZCIDV
 * setFlagsNZCV
 * setFlagsNZC
 * setFlagsNZ
 * +++--+ -> ADC, SBC
 * ++---- -> AND, DEC, DEX, DEY, EOR, INC, INX, INY, LDA, LDX, LDY, ORA, PLA, TAX, TAY, TSX, TXA, TYA
 * +++--- -> ASL, CMP, CPX, CPY, ROL, ROR
 *           BIT
 * ---1-- -> BRK
 * --0--- -> CLC
 * ----0- -> CLD
 * ---0-- -> CLI
 * -----0 -> CLV
 * 0++--- -> LSR
 *        -> PLP
 *        -> RTI
 * --1--- -> SEC
 * ----1- -> SED
 * ---1-- -> SEI
 *
 * setSignableFlags
 * setComparableFlags
 * setArithmeticFlags
*/

