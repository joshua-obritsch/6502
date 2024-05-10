#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(TXS, {
    TEST("TXS implied", {
        // Given:
        cpu.x              = 0xD1;
        cpu.memory[0xFFFC] = TXS_IMPL;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 2     );
        EXPECT_EQ(cpu.pc, 0xFFFD);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0xD1  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xD1  );
    })
})
