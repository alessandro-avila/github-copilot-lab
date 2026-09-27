/*
 * test_checksum.c - tests for checksum.c
 *
 * One test per scenario in specs/checksum.spec.md. chk() returns 1 when a
 * code passes and 0 when it fails. The tests pin down what chk() does
 * today, flagged scenarios included.
 */
#include "checksum.h"
#include "test.h"

/* Scenario 1 */
static void code_with_right_check_digit_passes(void)
{
    CHECK_EQ(1, chk("30123458"));
}

/* Scenario 2 */
static void code_with_wrong_check_digit_fails(void)
{
    CHECK_EQ(0, chk("30123459"));
}

/* Scenario 3 */
static void code_with_a_letter_fails(void)
{
    CHECK_EQ(0, chk("3012A458"));
}

/* Scenario 4 */
static void code_shorter_than_two_digits_fails(void)
{
    CHECK_EQ(0, chk("7"));
}

/* Scenario 5 */
static void code_longer_than_18_digits_fails(void)
{
    CHECK_EQ(0, chk("3012345678901234567"));
}

/* Scenario 6 - flagged: see spec */
static void two_digit_code_passes(void)
{
    CHECK_EQ(1, chk("17"));
}

/* Scenario 7 - flagged: see spec */
static void code_of_all_zeros_passes(void)
{
    CHECK_EQ(1, chk("00000000"));
}

int main(void)
{
    RUN(code_with_right_check_digit_passes);
    RUN(code_with_wrong_check_digit_fails);
    RUN(code_with_a_letter_fails);
    RUN(code_shorter_than_two_digits_fails);
    RUN(code_longer_than_18_digits_fails);
    RUN(two_digit_code_passes);
    RUN(code_of_all_zeros_passes);
    return TEST_SUMMARY();
}
