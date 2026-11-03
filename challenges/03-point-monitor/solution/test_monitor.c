/*
 * test_monitor.c - tests for monitor.c (reference solution)
 *
 * One test per scenario in monitor.spec.md, with the provided fake
 * monitoring unit. Every test starts with the Background: a freshly
 * started monitor at 10:00. The tests pin down what monitor_step() does
 * today, flagged scenarios included.
 */
#include "fake_mu.h"
#include "monitor.h"
#include "test.h"

/* Background: a freshly started monitor, at 10:00 */
static void start(void)
{
    fake_mu_reset();
    monitor_init();
}

/* Scenario 1 */
static void without_a_throw_the_monitor_does_nothing(void)
{
    start();
    CHECK_EQ(0, monitor_step());
    CHECK_EQ(0, fake.alerts);
}

/* Scenario 2 */
static void normal_throw_sends_no_alert(void)
{
    start();
    fake_throw("P101", 3200);
    CHECK_EQ(1, monitor_step());
    CHECK_EQ(0, fake.alerts);
}

/* Scenario 3 */
static void slow_throw_sends_a_warning(void)
{
    start();
    fake_throw("P101", 4500);
    CHECK_EQ(2, monitor_step());
    CHECK_EQ(1, fake.alerts);
    CHECK_EQ(1, fake.last_level);
    CHECK_STR_EQ("P101", fake.last_pt);
}

/* Scenario 4 */
static void too_slow_throw_sends_an_alarm(void)
{
    start();
    fake_throw("P101", 7000);
    CHECK_EQ(3, monitor_step());
    CHECK_EQ(1, fake.alerts);
    CHECK_EQ(2, fake.last_level);
    CHECK_STR_EQ("P101", fake.last_pt);
}

/* Scenario 5 */
static void third_slow_throw_in_a_row_sends_an_alarm(void)
{
    start();
    fake_throw("P101", 4500);
    fake_throw("P101", 4600);
    fake_throw("P101", 4700);
    monitor_step();
    monitor_step();
    CHECK_EQ(3, monitor_step());
    CHECK_EQ(2, fake.last_level);
    CHECK_STR_EQ("P101", fake.last_pt);
}

/* Scenario 6 */
static void normal_throw_restarts_the_count(void)
{
    start();
    fake_throw("P101", 4500);
    fake_throw("P101", 4600);
    fake_throw("P101", 3200);
    fake_throw("P101", 4700);
    monitor_step();
    monitor_step();
    monitor_step();
    CHECK_EQ(2, monitor_step());
    CHECK_EQ(1, fake.last_level);
}

/* Scenario 7 - flagged: see spec */
static void slow_throws_on_different_points_add_up(void)
{
    start();
    fake_throw("P101", 4500);
    fake_throw("P102", 4600);
    fake_throw("P103", 4700);
    monitor_step();
    monitor_step();
    CHECK_EQ(3, monitor_step());
    CHECK_EQ(2, fake.last_level);
    CHECK_STR_EQ("P103", fake.last_pt);
}

/* Scenario 8 - flagged: see spec */
static void normal_throw_on_other_points_restarts_the_count(void)
{
    start();
    fake_throw("P101", 4500);
    fake_throw("P101", 4600);
    fake_throw("P102", 3200);
    fake_throw("P101", 4700);
    monitor_step();
    monitor_step();
    monitor_step();
    CHECK_EQ(2, monitor_step());
    CHECK_EQ(1, fake.last_level);
    CHECK_STR_EQ("P101", fake.last_pt);
}

/* Scenario 9 - flagged: see spec */
static void at_23_30_a_slow_throw_still_sends_a_warning(void)
{
    start();
    fake.hour = 23;   /* 23:30: the clock reports whole hours */
    fake_throw("P101", 4500);
    CHECK_EQ(2, monitor_step());
    CHECK_EQ(1, fake.alerts);
    CHECK_EQ(1, fake.last_level);
}

/* Scenario 10 - flagged: see spec */
static void at_02_00_a_too_slow_throw_still_sends_an_alarm(void)
{
    start();
    fake.hour = 2;
    fake_throw("P101", 7000);
    CHECK_EQ(3, monitor_step());
    CHECK_EQ(1, fake.alerts);
    CHECK_EQ(2, fake.last_level);
}

/* Scenario 11 - flagged: see spec */
static void after_an_alarm_the_next_slow_throw_sends_a_warning(void)
{
    start();
    fake_throw("P101", 4500);
    fake_throw("P101", 4600);
    fake_throw("P101", 4700);
    fake_throw("P101", 4800);
    monitor_step();
    monitor_step();
    monitor_step();
    CHECK_EQ(2, monitor_step());
    CHECK_EQ(1, fake.last_level);
}

int main(void)
{
    RUN(without_a_throw_the_monitor_does_nothing);
    RUN(normal_throw_sends_no_alert);
    RUN(slow_throw_sends_a_warning);
    RUN(too_slow_throw_sends_an_alarm);
    RUN(third_slow_throw_in_a_row_sends_an_alarm);
    RUN(normal_throw_restarts_the_count);
    RUN(slow_throws_on_different_points_add_up);
    RUN(normal_throw_on_other_points_restarts_the_count);
    RUN(at_23_30_a_slow_throw_still_sends_a_warning);
    RUN(at_02_00_a_too_slow_throw_still_sends_an_alarm);
    RUN(after_an_alarm_the_next_slow_throw_sends_a_warning);
    return TEST_SUMMARY();
}
