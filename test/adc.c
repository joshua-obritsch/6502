#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(ADC, {
    TEST("ADC immediate", {
        // Given:
        cpu.memory[0xFFFC] = ADC_IMM;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 2     );
        EXPECT_EQ(cpu.pc, 0xFFFE);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x06  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })
})
