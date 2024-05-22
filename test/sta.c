#include "cpu.h"
#include "instructions.h"
#include "test.h"

TEST_SUITE(STA, {
    TEST("STA zeropage", {
        // Given:
        cpu.ac             = 0x5C;
        cpu.memory[0xFFFC] = STA_ZPG;
        cpu.memory[0xFFFD] = 0x6B;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 3     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0x5C  );
        EXPECT_EQ(cpu.x             , 0x00  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x006B], 0x5C  );
    })

    TEST("STA zeropage,X", {
        // Given:
        cpu.ac             = 0xD1;
        cpu.x              = 0x66;
        cpu.memory[0xFFFC] = STA_ZPGX;
        cpu.memory[0xFFFD] = 0x06;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 4     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0xD1  );
        EXPECT_EQ(cpu.x             , 0x66  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x006C], 0xD1  );
    })

    TEST("STA zeropage,X with wrapping", {
        // Given:
        cpu.ac             = 0x4D;
        cpu.x              = 0x5E;
        cpu.memory[0xFFFC] = STA_ZPGX;
        cpu.memory[0xFFFD] = 0xCB;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 4     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0x4D  );
        EXPECT_EQ(cpu.x             , 0x5E  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x0029], 0x4D  );
    })

    TEST("STA absolute", {
        // Given:
        cpu.ac             = 0xF1;
        cpu.memory[0xFFFC] = STA_ABS;
        cpu.memory[0xFFFD] = 0xDA;
        cpu.memory[0xFFFE] = 0x40;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 4     );
        EXPECT_EQ(cpu.pc            , 0xFFFF);
        EXPECT_EQ(cpu.ac            , 0xF1  );
        EXPECT_EQ(cpu.x             , 0x00  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x40DA], 0xF1  );
    })

    TEST("STA absolute,X", {
        // Given:
        cpu.ac             = 0x69;
        cpu.x              = 0x8F;
        cpu.memory[0xFFFC] = STA_ABSX;
        cpu.memory[0xFFFD] = 0x3D;
        cpu.memory[0xFFFE] = 0x1F;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 5     );
        EXPECT_EQ(cpu.pc            , 0xFFFF);
        EXPECT_EQ(cpu.ac            , 0x69  );
        EXPECT_EQ(cpu.x             , 0x8F  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x1FCC], 0x69  );
    })

    TEST("STA absolute,Y", {
        // Given:
        cpu.ac             = 0x0E;
        cpu.y              = 0xF9;
        cpu.memory[0xFFFC] = STA_ABSY;
        cpu.memory[0xFFFD] = 0x92;
        cpu.memory[0xFFFE] = 0x0C;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 5     );
        EXPECT_EQ(cpu.pc            , 0xFFFF);
        EXPECT_EQ(cpu.ac            , 0x0E  );
        EXPECT_EQ(cpu.x             , 0x00  );
        EXPECT_EQ(cpu.y             , 0xF9  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x0D8B], 0x0E  );
    })

    TEST("STA (indirect,X)", {
        // Given:
        cpu.ac             = 0xD9;
        cpu.x              = 0x3B;
        cpu.memory[0x0060] = 0xDA;
        cpu.memory[0x0061] = 0x38;
        cpu.memory[0xFFFC] = STA_INDX;
        cpu.memory[0xFFFD] = 0x25;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 6     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0xD9  );
        EXPECT_EQ(cpu.x             , 0x3B  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x38DA], 0xD9  );
    })

    TEST("STA (indirect,X) with wrapping", {
        // Given:
        cpu.ac             = 0x07;
        cpu.x              = 0xE8;
        cpu.memory[0x007D] = 0x35;
        cpu.memory[0x007E] = 0x31;
        cpu.memory[0xFFFC] = STA_INDX;
        cpu.memory[0xFFFD] = 0x95;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 6     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0x07  );
        EXPECT_EQ(cpu.x             , 0xE8  );
        EXPECT_EQ(cpu.y             , 0x00  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x3135], 0x07  );
    })

    TEST("STA (indirect),Y", {
        // Given:
        cpu.ac             = 0xF2;
        cpu.y              = 0x52;
        cpu.memory[0x000A] = 0x5E;
        cpu.memory[0x000B] = 0x41;
        cpu.memory[0xFFFC] = STA_INDY;
        cpu.memory[0xFFFD] = 0x0A;

        // When:
        cycles = executeInstruction(&cpu);

        // Then:
        EXPECT_EQ(cycles            , 6     );
        EXPECT_EQ(cpu.pc            , 0xFFFE);
        EXPECT_EQ(cpu.ac            , 0xF2  );
        EXPECT_EQ(cpu.x             , 0x00  );
        EXPECT_EQ(cpu.y             , 0x52  );
        EXPECT_EQ(cpu.sr            , 0x00  );
        EXPECT_EQ(cpu.sp            , 0xFF  );
        EXPECT_EQ(cpu.memory[0x41B0], 0xF2  );
    })
})
