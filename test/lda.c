#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(LDA, {
    TEST("LDA immediate", {
        // Given:
        cpu.memory[0xFFFC] = LDA_IMM;
        cpu.memory[0xFFFD] = 0x79;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 2     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x79  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA zeropage", {
        // Given:
        cpu.memory[0x00F5] = 0xDD;
        cpu.memory[0xFFFC] = LDA_ZPG;
        cpu.memory[0xFFFD] = 0xF5;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 3     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0xDD  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA zeropage,X", {
        // Given:
        cpu.x              = 0xAB;
        cpu.memory[0x00D8] = 0xD7;
        cpu.memory[0xFFFC] = LDA_ZPGX;
        cpu.memory[0xFFFD] = 0x2D;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0xD7  );
        EXPECT_EQ(cpu.x , 0xAB  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA zeropage,X with wrapping", {
        // Given:
        cpu.x              = 0xBE;
        cpu.memory[0x001B] = 0x07;
        cpu.memory[0xFFFC] = LDA_ZPGX;
        cpu.memory[0xFFFD] = 0x5D;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x07  );
        EXPECT_EQ(cpu.x , 0xBE  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA absolute", {
        // Given:
        cpu.memory[0x3853] = 0x24;
        cpu.memory[0xFFFC] = LDA_ABS;
        cpu.memory[0xFFFD] = 0x53;
        cpu.memory[0xFFFE] = 0x38;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0x24  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA absolute,X", {
        // Given:
        cpu.x              = 0xAC;
        cpu.memory[0xB2B7] = 0x2B;
        cpu.memory[0xFFFC] = LDA_ABSX;
        cpu.memory[0xFFFD] = 0x0B;
        cpu.memory[0xFFFE] = 0xB2;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0x2B  );
        EXPECT_EQ(cpu.x , 0xAC  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA absolute,X with crossed page boundary", {
        // Given:
        cpu.x              = 0xB9;
        cpu.memory[0xF307] = 0x0B;
        cpu.memory[0xFFFC] = LDA_ABSX;
        cpu.memory[0xFFFD] = 0x4E;
        cpu.memory[0xFFFE] = 0xF2;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 5     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0x0B  );
        EXPECT_EQ(cpu.x , 0xB9  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA absolute,Y", {
        // Given:
        cpu.y              = 0x23;
        cpu.memory[0xA1D3] = 0xE0;
        cpu.memory[0xFFFC] = LDA_ABSY;
        cpu.memory[0xFFFD] = 0xB0;
        cpu.memory[0xFFFE] = 0xA1;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0xE0  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x23  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA absolute,Y with crossed page boundary", {
        // Given:
        cpu.y              = 0x7F;
        cpu.memory[0x4B2D] = 0x8A;
        cpu.memory[0xFFFC] = LDA_ABSY;
        cpu.memory[0xFFFD] = 0xAE;
        cpu.memory[0xFFFE] = 0x4A;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 5     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0x8A  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x7F  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA (indirect,X)", {
        // Given:
        cpu.x              = 0x3C;
        cpu.memory[0x0081] = 0xDA;
        cpu.memory[0x0082] = 0xF7;
        cpu.memory[0xF7DA] = 0xDD;
        cpu.memory[0xFFFC] = LDA_INDX;
        cpu.memory[0xFFFD] = 0x45;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 6     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0xDD  );
        EXPECT_EQ(cpu.x , 0x3C  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA (indirect,X) with wrapping", {
        // Given:
        cpu.x              = 0xA9;
        cpu.memory[0x003F] = 0xF4;
        cpu.memory[0x0040] = 0x57;
        cpu.memory[0x57F4] = 0x21;
        cpu.memory[0xFFFC] = LDA_INDX;
        cpu.memory[0xFFFD] = 0x96;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 6     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x21  );
        EXPECT_EQ(cpu.x , 0xA9  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA (indirect),Y", {
        // Given:
        cpu.y              = 0x42;
        cpu.memory[0x0074] = 0xBA;
        cpu.memory[0x0075] = 0xDB;
        cpu.memory[0xDBFC] = 0x11;
        cpu.memory[0xFFFC] = LDA_INDY;
        cpu.memory[0xFFFD] = 0x74;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 5     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x11  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x42  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDA (indirect),Y with crossed page boundary", {
        // Given:
        cpu.y              = 0x92;
        cpu.memory[0x00C2] = 0xC7;
        cpu.memory[0x00C3] = 0x14;
        cpu.memory[0x1559] = 0x21;
        cpu.memory[0xFFFC] = LDA_INDY;
        cpu.memory[0xFFFD] = 0xC2;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 6     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x21  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x92  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })
})
