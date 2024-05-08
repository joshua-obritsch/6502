#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(STX, {
    TEST("STX zeropage", {
        // Given:
        cpu.x              = 0xAD;
        cpu.memory[0xFFFC] = STX_ZPG;
        cpu.memory[0xFFFD] = 0x3D;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 3     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0x00  );
        EXPECT_EQ(cpu.x             , 0xAD  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0x00  );
        EXPECT_EQ(cpu.memory[0x003D], 0xAD  );
    })

    TEST("STX zeropage,Y", {
        // Given:
        cpu.x              = 0xC7;
        cpu.y              = 0x82;
        cpu.memory[0xFFFC] = STX_ZPGY;
        cpu.memory[0xFFFD] = 0x46;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 4     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0x00  );
        EXPECT_EQ(cpu.x             , 0xC7  );
        EXPECT_EQ(cpu.y             , 0x82  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0x00  );
        EXPECT_EQ(cpu.memory[0x00C8], 0xC7  );
    })

    TEST("STX zeropage,Y with wrapping", {
        // Given:
        cpu.x              = 0x18;
        cpu.y              = 0xA4;
        cpu.memory[0xFFFC] = STX_ZPGY;
        cpu.memory[0xFFFD] = 0x83;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 4     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0x00  );
        EXPECT_EQ(cpu.x             , 0x18  );
        EXPECT_EQ(cpu.y             , 0xA4  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0x00  );
        EXPECT_EQ(cpu.memory[0x0027], 0x18  );
    })

    TEST("STX absolute", {
        // Given:
        cpu.x              = 0x5C;
        cpu.memory[0xFFFC] = STX_ABS;
        cpu.memory[0xFFFD] = 0x76;
        cpu.memory[0xFFFE] = 0x63;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 4     );
        EXPECT_EQ(cpu.pc            , 0xFFFF);
        EXPECT_EQ(cpu.ac            , 0x00  );
        EXPECT_EQ(cpu.x             , 0x5C  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0x00  );
        EXPECT_EQ(cpu.memory[0x6376], 0x5C  );
    })
})
