#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(TAY, {
    TEST("TAY implied", {
        // Given:
        cpu.ac             = 0x19;
        cpu.memory[0xFFFC] = TAY_IMPL;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 2     );
        EXPECT_EQ(cpu.pc, 0xFFFD);
        EXPECT_EQ(cpu.ac, 0x19  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x19  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })
})
