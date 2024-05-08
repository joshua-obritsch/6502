#ifndef TEST_H
#define TEST_H

#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define intlen(num) (num == 0 ? 1 : (int)log10(num) + 1)
#define repeat(c, count) for (int i = 0; i < count; i++) { printf(c); }

#define RESET  "\033[0m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define ORANGE "\033[33m"

#define TITLE(title, name) \
    printf("╔═[%s: %s]═", title, name); \
    repeat("═", 72 - strlen(title) - strlen(name)); \
    printf("╗\n")

#define BOTTOM    printf("╚"); repeat("═", 78); printf("╝\n")
#define SEPARATOR printf("╟"); repeat("─", 78); printf("╢\n")

#define PASS_NAME(name) \
    printf("║ " GREEN "PASS" RESET ": %s", name); \
    repeat(" ", 71 - strlen(name)); \
    printf("║\n")

#define FAIL_NAME(name) \
    printf("║ " RED "FAIL" RESET ": %s", name); \
    repeat(" ", 71 - strlen(name)); \
    printf("║\n")

#define DONE_COUNT \
    if (localTestCount > 0) { \
        printf("║ DONE: %d", localTestCount); \
        repeat(" ", 71 - intlen(localTestCount)); \
        printf("║\n"); \
    } else { \
        printf("║ SKIPPED"); \
        repeat(" ", 70); \
        printf("║\n"); \
    }

#define FAIL_COUNT \
    if (localTestPassedCount < localTestCount) { \
        int count = localTestCount - localTestPassedCount; \
        printf("║ " RED "FAIL" RESET ": %d", count); \
        repeat(" ", 71 - intlen(count)); \
        printf("║\n"); \
    }

#define PASS_COUNT \
    if (localTestPassedCount > 0) { \
        printf("║ \033[32mPASS\033[0m: %d", localTestPassedCount); \
        repeat(" ", 71 - intlen(localTestPassedCount)); \
        printf("║\n"); \
    }

#define FAIL_EQ(a, b) \
    printf("║       > %s:%d ", __FILE__, __LINE__); \
    { \
        int len \
            = strlen(__FILE__) \
            + intlen(__LINE__) \
            + intlen(a) \
            + intlen(b); \
        repeat("-", 61 - len); \
    } \
    printf(" \033[33m%d\033[0m \033[31m!=\033[0m \033[33m%d\033[0m", a, b); \
    printf(" ║\n");

#define TEST_SUITE(name, block) \
    extern Cpu cpu; \
    extern int cycles; \
    extern int localExpectCount; \
    extern int localExpectPassedCount; \
    extern int localTestCount; \
    extern int localTestPassedCount; \
    extern int totalTestCount; \
    extern int totalTestPassedCount; \
    extern int testSuite; \
    extern char* testName; \
    void name() { \
        if (testName == NULL || !testSuite || !strcasecmp(testName, #name)) { \
            localTestCount = 0; \
            localTestPassedCount = 0; \
            TITLE("TEST SUITE", #name); \
            block; \
            if (localTestCount > 0) SEPARATOR; \
            DONE_COUNT; \
            FAIL_COUNT; \
            PASS_COUNT; \
            BOTTOM; \
            printf("\n"); \
        } \
    }

#define TEST(name, block) \
    if (testName == NULL || testSuite || !strcasecmp(testName, name)) { \
        int secondPass = 0; \
        localExpectCount = 0; \
        localExpectPassedCount = 0; \
        localTestCount++; \
        totalTestCount++; \
        resetCpu(&cpu); \
        block; \
        if (localExpectPassedCount == localExpectCount) { \
            localTestPassedCount++; \
            totalTestPassedCount++; \
            PASS_NAME(name); \
        } else { \
            FAIL_NAME(name); \
        } \
        secondPass = 1; \
        resetCpu(&cpu); \
        block; \
    }

#define EXPECT_EQ(a, b) \
    if (secondPass == 0) { \
        localExpectCount += 1; \
        localExpectPassedCount += a == b; \
    } else if (a != b) { \
        FAIL_EQ(a, b); \
    }

#endif // TEST_H
