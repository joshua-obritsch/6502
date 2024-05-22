#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(JMP, {
    TEST("JMP absolute", {
        // Given:
        cpu.memory[0xFFFC] = JMP_ABS;
        cpu.memory[0xFFFD] = 0x29;
        cpu.memory[0xFFFE] = 0x57;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 3     );
        EXPECT_EQ(cpu.pc, 0x5729);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })

    TEST("JMP indirect", {
        // Given:
        cpu.memory[0xCCA2] = 0x8B;
        cpu.memory[0xCCA3] = 0x1B;
        cpu.memory[0xFFFC] = JMP_IND;
        cpu.memory[0xFFFD] = 0xA2;
        cpu.memory[0xFFFE] = 0xCC;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles, 5     );
        EXPECT_EQ(cpu.pc, 0x1B8B);
        EXPECT_EQ(cpu.ac, 0x00  );
        EXPECT_EQ(cpu.x , 0x00  );
        EXPECT_EQ(cpu.y , 0x00  );
        EXPECT_EQ(cpu.sr, 0x00  );
        EXPECT_EQ(cpu.sp, 0xFF  );
    })
})
