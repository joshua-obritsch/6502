#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(RTS, {
    TEST("RTS absolute", {
        // Given:
        cpu.sp             = 0xFD;
        cpu.memory[0x01FF] = 0xAB;
        cpu.memory[0x01FE] = 0xD6;
        cpu.memory[0xFFFC] = RTS_IMPL;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 6     );
        EXPECT_EQ(cpu.pc, 0xD6AC);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })
})
