#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(JSR, {
    TEST("JSR absolute", {
        // Given:
        cpu.memory[0xFFFC] = JSR_ABS;
        cpu.memory[0xFFFD] = 0x2C;
        cpu.memory[0xFFFE] = 0x26;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 6     );
        EXPECT_EQ(cpu.pc            , 0x262C);
        EXPECT_EQ(cpu.ac            , 0x00  );
        EXPECT_EQ(cpu.x             , 0x00  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFD  );
        EXPECT_EQ(cpu.memory[0x01FF], 0xFE  );
        EXPECT_EQ(cpu.memory[0x01FE], 0xFF  );
    })
})
