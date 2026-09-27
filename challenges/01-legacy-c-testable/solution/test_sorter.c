/*
 * test_sorter.c - tests for sorter.c (reference solution)
 *
 * One test per scenario in sorter.spec.md, using the provided fake
 * hardware in legacy-c/tests/fake_hw.h. sorter.c and route.c still print
 * to the console; the tests do not check that output.
 */
#include "fake_hw.h"
#include "sorter.h"
#include "test.h"

/* Background: a freshly started sorter, at 10:00 UTC */
static void background(void)
{
    fake_hw_reset();
    sorter_init();
}

/* Scenario 1 */
static void without_a_parcel_the_sorter_does_nothing(void)
{
    background();

    CHECK_EQ(0, sorter_step());          /* 0 = no parcel */
    CHECK_EQ(0, fake.reads_done);
    CHECK_EQ(0, fake.diverts);
    CHECK_EQ(0, fake.releases);
}

/* Scenario 2 */
static void readable_parcel_goes_into_its_chute(void)
{
    background();
    fake.parcel_present = 1;
    fake.reads[0] = "30123458";

    sorter_step();
    CHECK_EQ(3, fake.last_chute);
}

/* Scenario 3 */
static void after_a_failed_read_the_sorter_reads_again(void)
{
    background();
    fake.parcel_present = 1;             /* no reads set: every read fails */

    CHECK_EQ(1, sorter_step());          /* 1 = read again */
    CHECK_EQ(0, fake.diverts);
    CHECK_EQ(0, fake.releases);
}

/* Scenario 4 - flagged: see spec */
static void after_five_failed_reads_the_sorter_gives_up(void)
{
    int step;

    background();
    fake.parcel_present = 1;

    for (step = 1; step <= 4; step++)
        sorter_step();
    CHECK_EQ(0, fake.releases);
    sorter_step();
    CHECK_EQ(1, fake.releases);
}

/* Scenario 5 - flagged: see spec */
static void wrong_check_digit_counts_as_a_failed_read(void)
{
    background();
    fake.parcel_present = 1;
    fake.reads[0] = "30123459";

    CHECK_EQ(1, sorter_step());          /* 1 = read again */
    CHECK_EQ(0, fake.diverts);
}

/* Scenario 6 */
static void parcel_read_on_the_third_try_goes_into_its_chute(void)
{
    background();
    fake.parcel_present = 1;
    fake.reads[2] = "30123458";          /* reads 1 and 2 fail */

    sorter_step();
    sorter_step();
    CHECK_EQ(0, fake.diverts);
    sorter_step();
    CHECK_EQ(3, fake.last_chute);
}

/* Scenario 7 - flagged: see spec */
static void next_parcel_inherits_the_failed_reads(void)
{
    background();
    fake.parcel_present = 1;             /* the next parcel is right behind */
    fake.reads[2] = "30123458";          /* first parcel: diverted on read 3 */

    sorter_step();
    sorter_step();
    sorter_step();
    CHECK_EQ(1, fake.diverts);

    sorter_step();                       /* next parcel: every read fails */
    sorter_step();
    CHECK_EQ(0, fake.releases);
    sorter_step();
    CHECK_EQ(1, fake.releases);          /* after three reads, not five */
}

/* Scenario 8 */
static void parcel_without_a_route_goes_into_chute_9(void)
{
    background();
    fake.parcel_present = 1;
    fake.reads[0] = "55123457";

    sorter_step();
    CHECK_EQ(9, fake.last_chute);
}

/* Scenario 9 */
static void at_17_59_utc_a_parcel_goes_into_its_own_chute(void)
{
    background();
    fake.now = fake_time(17, 59);
    fake.parcel_present = 1;
    fake.reads[0] = "30123458";

    sorter_step();
    CHECK_EQ(3, fake.last_chute);
}

/* Scenario 10 - flagged: see spec */
static void from_18_00_utc_every_parcel_goes_into_chute_8(void)
{
    background();
    fake.now = fake_time(18, 0);
    fake.parcel_present = 1;
    fake.reads[0] = "30123458";

    sorter_step();
    CHECK_EQ(8, fake.last_chute);
}

int main(void)
{
    RUN(without_a_parcel_the_sorter_does_nothing);
    RUN(readable_parcel_goes_into_its_chute);
    RUN(after_a_failed_read_the_sorter_reads_again);
    RUN(after_five_failed_reads_the_sorter_gives_up);
    RUN(wrong_check_digit_counts_as_a_failed_read);
    RUN(parcel_read_on_the_third_try_goes_into_its_chute);
    RUN(next_parcel_inherits_the_failed_reads);
    RUN(parcel_without_a_route_goes_into_chute_9);
    RUN(at_17_59_utc_a_parcel_goes_into_its_own_chute);
    RUN(from_18_00_utc_every_parcel_goes_into_chute_8);
    return TEST_SUMMARY();
}
