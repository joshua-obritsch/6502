#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(TSX, {
    TEST("TSX implied", {
        // Given:
        cpu.sp             = 0x01;
        cpu.memory[0x0100] = 0xBE;
        cpu.memory[0xFFFC] = TSX_IMPL;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 2     );
        EXPECT_EQ(cpu.pc, 0xFFFD);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0xBE  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })
})
