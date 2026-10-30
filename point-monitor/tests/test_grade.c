/*
 * test_grade.c - tests for grade.c
 *
 * One test per scenario in specs/grade.spec.md. grade() returns 0 for an
 * ok throw, 1 for a slow one and 2 for one that is too slow. The tests
 * pin down what grade() does today, flagged scenarios included.
 */
#include "grade.h"
#include "test.h"

/* Scenario 1 */
static void normal_throw_is_ok(void)
{
    CHECK_EQ(0, grade(3200));
}

/* Scenario 2 */
static void throw_of_4500_ms_is_slow(void)
{
    CHECK_EQ(1, grade(4500));
}

/* Scenario 3 */
static void throw_of_7000_ms_is_too_slow(void)
{
    CHECK_EQ(2, grade(7000));
}

/* Scenario 4 */
static void throw_of_exactly_4000_ms_is_still_ok(void)
{
    CHECK_EQ(0, grade(4000));
}

/* Scenario 5 */
static void throw_of_exactly_6000_ms_is_slow(void)
{
    CHECK_EQ(1, grade(6000));
}

/* Scenario 6 - flagged: see spec */
static void throw_of_0_ms_is_ok(void)
{
    CHECK_EQ(0, grade(0));
}

/* Scenario 7 - flagged: see spec */
static void negative_time_is_ok(void)
{
    CHECK_EQ(0, grade(-50));
}

int main(void)
{
    RUN(normal_throw_is_ok);
    RUN(throw_of_4500_ms_is_slow);
    RUN(throw_of_7000_ms_is_too_slow);
    RUN(throw_of_exactly_4000_ms_is_still_ok);
    RUN(throw_of_exactly_6000_ms_is_slow);
    RUN(throw_of_0_ms_is_ok);
    RUN(negative_time_is_ok);
    return TEST_SUMMARY();
}
