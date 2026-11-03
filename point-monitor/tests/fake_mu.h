/*
 * fake_mu.h - fake monitoring unit for the tests (provided)
 *
 * The monitor tests link fake_mu.c instead of mu.c. A test queues the
 * throws the unit reports and sets the clock, runs the monitor, then
 * checks the alerts the fake recorded:
 *
 *   fake_mu_reset();             no throws, 10:00, nothing recorded
 *   monitor_init();              a freshly started monitor
 *   fake_throw("P101", 4500);    next throw: points P101, 4500 ms
 *   CHECK_EQ(2, monitor_step());
 *   CHECK_EQ(1, fake.alerts);
 *   CHECK_STR_EQ("P101", fake.last_pt);
 *   CHECK_EQ(1, fake.last_level);
 *
 * You do not need to change this file.
 */
#ifndef FAKE_MU_H
#define FAKE_MU_H

#define FAKE_MAX_THROWS 10

struct fake_mu {
    /* set by the test */
    const char *pts[FAKE_MAX_THROWS];  /* points of each queued throw */
    int ms[FAKE_MAX_THROWS];           /* how long each queued throw took */
    int queued;                        /* throws queued so far */
    int hour;                          /* what the clock says, 0-23 */

    /* recorded by the fake */
    int throws_taken;                  /* throws the monitor took so far */
    int alerts;                        /* alerts sent so far */
    char last_pt[16];                  /* points of the last alert, "" = none */
    int last_level;                    /* last alert: 1 = warning, 2 = alarm, 0 = none */
};

extern struct fake_mu fake;

/* no throws, 10:00, nothing recorded */
void fake_mu_reset(void);

/* queues the next throw the unit reports: which points, how many ms */
void fake_throw(const char *pt, int ms);

#endif
