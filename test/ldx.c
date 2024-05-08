#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(LDX, {
    TEST("LDX immediate", {
        // Given:
        cpu.memory[0xFFFC] = LDX_IMM;
        cpu.memory[0xFFFD] = 0x06;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 2     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x06  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDX zeropage", {
        // Given:
        cpu.memory[0x009E] = 0x8A;
        cpu.memory[0xFFFC] = LDX_ZPG;
        cpu.memory[0xFFFD] = 0x9E;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 3     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x8A  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDX zeropage,Y", {
        // Given:
        cpu.y              = 0x08;
        cpu.memory[0x0090] = 0xD7;
        cpu.memory[0xFFFC] = LDX_ZPGY;
        cpu.memory[0xFFFD] = 0x88;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0xD7  );
        EXPECT_EQ(cpu.y , 0x08  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDX zeropage,Y with wrapping", {
        // Given:
        cpu.y              = 0xE5;
        cpu.memory[0x00C5] = 0x3B;
        cpu.memory[0xFFFC] = LDX_ZPGY;
        cpu.memory[0xFFFD] = 0xE0;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x3B  );
        EXPECT_EQ(cpu.y , 0xE5  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDX absolute", {
        // Given:
        cpu.memory[0xF678] = 0x87;
        cpu.memory[0xFFFC] = LDX_ABS;
        cpu.memory[0xFFFD] = 0x78;
        cpu.memory[0xFFFE] = 0xF6;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x87  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDX absolute,Y", {
        // Given:
        cpu.y              = 0x35;
        cpu.memory[0xA2C1] = 0xF2;
        cpu.memory[0xFFFC] = LDX_ABSY;
        cpu.memory[0xFFFD] = 0x8C;
        cpu.memory[0xFFFE] = 0xA2;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 4     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0xF2  );
        EXPECT_EQ(cpu.y , 0x35  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })

    TEST("LDX absolute,Y with crossed page boundary", {
        // Given:
        cpu.y              = 0xEF;
        cpu.memory[0x6188] = 0x0F;
        cpu.memory[0xFFFC] = LDX_ABSY;
        cpu.memory[0xFFFD] = 0x99;
        cpu.memory[0xFFFE] = 0x60;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 5     );
        EXPECT_EQ(cpu.pc, 0xFFFF);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x0F  );
        EXPECT_EQ(cpu.y , 0xEF  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })
})
