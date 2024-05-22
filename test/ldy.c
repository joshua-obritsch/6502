#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(LDY, {
    TEST("LDY immediate", {
        // Given:
        cpu.memory[0xFFFC] = LDY_IMM;
        cpu.memory[0xFFFD] = 0xFE;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 2     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0xFE  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })

    TEST("LDY zeropage", {
        // Given:
        cpu.memory[0x00B6] = 0x2E;
        cpu.memory[0xFFFC] = LDY_ZPG;
        cpu.memory[0xFFFD] = 0xB6;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 3     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x2E  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })

    TEST("LDY zeropage,X", {
        // Given:
        cpu.x              = 0x61;
        cpu.memory[0x00B0] = 0x45;
        cpu.memory[0xFFFC] = LDY_ZPGX;
        cpu.memory[0xFFFD] = 0x4F;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x61  );
        EXPECT_EQ(cpu.y , 0x45  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })

    TEST("LDY zeropage,X with wrapping", {
        // Given:
        cpu.x              = 0xC8;
        cpu.memory[0x0073] = 0x5A;
        cpu.memory[0xFFFC] = LDY_ZPGX;
        cpu.memory[0xFFFD] = 0xAB;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0xC8  );
        EXPECT_EQ(cpu.y , 0x5A  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })

    TEST("LDY absolute", {
        // Given:
        cpu.memory[0xC9AC] = 0x79;
        cpu.memory[0xFFFC] = LDY_ABS;
        cpu.memory[0xFFFD] = 0xAC;
        cpu.memory[0xFFFE] = 0xC9;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x79  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })

    TEST("LDY absolute,X", {
        // Given:
        cpu.x              = 0x25;
        cpu.memory[0x6E9D] = 0x63;
        cpu.memory[0xFFFC] = LDY_ABSX;
        cpu.memory[0xFFFD] = 0x78;
        cpu.memory[0xFFFE] = 0x6E;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x25  );
        EXPECT_EQ(cpu.y , 0x63  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })

    TEST("LDY absolute,X with crossed page boundary", {
        // Given:
        cpu.x              = 0xA3;
        cpu.memory[0x4715] = 0x5A;
        cpu.memory[0xFFFC] = LDY_ABSX;
        cpu.memory[0xFFFD] = 0x72;
        cpu.memory[0xFFFE] = 0x46;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 5     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0xA3  );
        EXPECT_EQ(cpu.y , 0x5A  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })
})
