/*
 * fake_hw.c - fake sorter hardware for the tests (provided)
 *
 * CMakeLists.txt links this file into the sorter tests in place of hw.c,
 * so sorter.c runs unchanged but talks to this fake. The fake prints
 * nothing: it returns what the test put in `fake` and records what the
 * sorter asked for. You do not need to change this file.
 */
#include <string.h>

#include "fake_hw.h"
#include "hw.h"

struct fake_hw fake;

time_t fake_time(int hour, int minute)
{
    return (time_t)(hour * 3600 + minute * 60);   /* 1 January 1970 */
}

void fake_hw_reset(void)
{
    int i;

    fake.parcel_present = 0;
    for (i = 0; i < FAKE_MAX_READS; i++)
        fake.reads[i] = NULL;
    fake.now = fake_time(10, 0);
    fake.reads_done = 0;
    fake.diverts = 0;
    fake.last_chute = -1;
    fake.releases = 0;
}

int hw_parcel_present(void)
{
    return fake.parcel_present;
}

int hw_read_barcode(char *buf, int n)
{
    const char *label = NULL;

    if (fake.reads_done < FAKE_MAX_READS)
        label = fake.reads[fake.reads_done];
    fake.reads_done++;

    if (label == NULL || (int)strlen(label) >= n)
        return -1;
    memcpy(buf, label, strlen(label) + 1);
    return 0;
}

void hw_divert(int chute)
{
    fake.diverts++;
    fake.last_chute = chute;
}

void hw_release(void)
{
    fake.releases++;
}

time_t hw_now(void)
{
    return fake.now;
}
