#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(TYA, {
    TEST("TYA implied", {
        // Given:
        cpu.y              = 0xFA;
        cpu.memory[0xFFFC] = TYA_IMPL;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 2     );
        EXPECT_EQ(cpu.pc, 0xFFFD);
        EXPECT_EQ(cpu.ac, 0xFA  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0xFA  );
        EXPECT_EQ(cpu.sr, 0x80  );
        EXPECT_EQ(cpu.sp, 0x00  );
    })
})
