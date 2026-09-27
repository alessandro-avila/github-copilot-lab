/*
 * test.h - a tiny test harness for the legacy C challenge
 *
 * No framework, no download. One test file per module:
 *
 *   static void adds_up(void) { CHECK_EQ(4, 2 + 2); }
 *   int main(void) { RUN(adds_up); return TEST_SUMMARY(); }
 *
 *   CHECK(condition)                fails when the condition is false
 *   CHECK_EQ(expected, actual)      compares two whole numbers
 *   CHECK_STR_EQ(expected, actual)  compares two strings
 *   RUN(test_function)              runs one test, prints PASS or FAIL
 *   TEST_SUMMARY()                  prints the totals; 0 = all passed, 1 = not
 */
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

static int test_count = 0;          /* tests run */
static int test_failed = 0;         /* tests with a failed check */
static int test_current_failed = 0; /* the running test has a failed check */

#define CHECK(condition)                                                   \
    do {                                                                   \
        if (!(condition)) {                                                \
            test_current_failed = 1;                                       \
            printf("    %s:%d: CHECK(%s) failed\n",                        \
                   __FILE__, __LINE__, #condition);                        \
        }                                                                  \
    } while (0)

#define CHECK_EQ(expected, actual)                                         \
    do {                                                                   \
        long long expected_ = (long long)(expected);                       \
        long long actual_ = (long long)(actual);                           \
        if (expected_ != actual_) {                                        \
            test_current_failed = 1;                                       \
            printf("    %s:%d: %s: expected %lld, got %lld\n",             \
                   __FILE__, __LINE__, #actual, expected_, actual_);       \
        }                                                                  \
    } while (0)

#define CHECK_STR_EQ(expected, actual)                                     \
    do {                                                                   \
        const char *expected_ = (expected);                                \
        const char *actual_ = (actual);                                    \
        if (actual_ == NULL || strcmp(expected_, actual_) != 0) {          \
            test_current_failed = 1;                                       \
            printf("    %s:%d: %s: expected \"%s\", got \"%s\"\n",         \
                   __FILE__, __LINE__, #actual, expected_,                 \
                   actual_ == NULL ? "(null)" : actual_);                  \
        }                                                                  \
    } while (0)

#define RUN(test_function)                                                 \
    do {                                                                   \
        test_current_failed = 0;                                           \
        test_function();                                                   \
        test_count++;                                                      \
        test_failed += test_current_failed;                                \
        printf("%s  %s\n", test_current_failed ? "FAIL" : "PASS",          \
               #test_function);                                            \
    } while (0)

#define TEST_SUMMARY()                                                     \
    (printf("\n%d tests, %d failed\n", test_count, test_failed),           \
     test_failed == 0 ? 0 : 1)

#endif
