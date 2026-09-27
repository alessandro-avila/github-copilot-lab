/*
 * fake_hw.h - fake sorter hardware for the tests (provided)
 *
 * The sorter tests link fake_hw.c instead of hw.c. A test sets what the
 * hardware reports, runs the sorter, then checks what the sorter did:
 *
 *   fake_hw_reset();              no parcel, every read fails, 10:00 UTC
 *   sorter_init();                a freshly started sorter
 *   fake.parcel_present = 1;
 *   fake.reads[0] = "30123458";   what the first read returns
 *   sorter_step();
 *   CHECK_EQ(3, fake.last_chute);
 *
 * The fake does not move parcels: fake.parcel_present stays as the test
 * set it, and fake.reads runs on from one parcel to the next.
 *
 * You do not need to change this file.
 */
#ifndef FAKE_HW_H
#define FAKE_HW_H

#include <time.h>

#define FAKE_MAX_READS 10

struct fake_hw {
    /* set by the test */
    int parcel_present;                 /* 1 = a parcel is at the scanner */
    const char *reads[FAKE_MAX_READS];  /* each read in order, NULL = no read */
    time_t now;                         /* what the clock says */

    /* recorded by the fake */
    int reads_done;                     /* reads so far */
    int diverts;                        /* diverts so far */
    int last_chute;                     /* chute of the last divert, -1 = none */
    int releases;                       /* releases to the end of the belt */
};

extern struct fake_hw fake;

/* no parcel, every read fails, 10:00 UTC, nothing recorded */
void fake_hw_reset(void);

/* a time of day in UTC, for fake.now */
time_t fake_time(int hour, int minute);

#endif
