#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(STY, {
    TEST("STY zeropage", {
        // Given:
        cpu.y              = 0x78;
        cpu.memory[0xFFFC] = STY_ZPG;
        cpu.memory[0xFFFD] = 0x44;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 3     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0x00  );
        EXPECT_EQ(cpu.x             , 0x00  );
        EXPECT_EQ(cpu.y             , 0x78  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x0044], 0x78  );
    })

    TEST("STY zeropage,X", {
        // Given:
        cpu.x              = 0x1F;
        cpu.y              = 0xBE;
        cpu.memory[0xFFFC] = STY_ZPGX;
        cpu.memory[0xFFFD] = 0x7B;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 4     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0x00  );
        EXPECT_EQ(cpu.x             , 0x1F  );
        EXPECT_EQ(cpu.y             , 0xBE  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x009A], 0xBE  );
    })

    TEST("STY zeropage,X with wrapping", {
        // Given:
        cpu.x              = 0x8E;
        cpu.y              = 0x36;
        cpu.memory[0xFFFC] = STY_ZPGX;
        cpu.memory[0xFFFD] = 0x91;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 4     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0x00  );
        EXPECT_EQ(cpu.x             , 0x8E  );
        EXPECT_EQ(cpu.y             , 0x36  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x001F], 0x36  );
    })

    TEST("STY absolute", {
        // Given:
        cpu.y              = 0xC0;
        cpu.memory[0xFFFC] = STY_ABS;
        cpu.memory[0xFFFD] = 0xAB;
        cpu.memory[0xFFFE] = 0xBD;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 4     );
        EXPECT_EQ(cpu.pc            , 0xFFFF);
        EXPECT_EQ(cpu.ac            , 0x00  );
        EXPECT_EQ(cpu.x             , 0x00  );
        EXPECT_EQ(cpu.y             , 0xC0  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0xBDAB], 0xC0  );
    })
})
