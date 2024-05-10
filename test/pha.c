#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(PHA, {
    TEST("PHA implied", {
        // Given:
        cpu.ac             = 0xA7;
        cpu.memory[0xFFFC] = PHA_IMPL;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 3     );
        EXPECT_EQ(cpu.pc            , 0xFFFD);
        EXPECT_EQ(cpu.ac            , 0xA7  );
        EXPECT_EQ(cpu.x             , 0x00  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0x01  );
        EXPECT_EQ(cpu.memory[0x0100], 0xA7  );
    })
})
