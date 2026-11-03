/*
 * fake_mu.c - fake monitoring unit for the tests (provided)
 *
 * CMakeLists.txt links this file into the monitor tests in place of
 * mu.c, so monitor.c runs unchanged but talks to this fake. The fake
 * prints nothing: it returns what the test put in `fake` and records the
 * alerts the monitor sent. You do not need to change this file.
 */
#include <stdio.h>
#include <string.h>

#include "fake_mu.h"
#include "mu.h"

struct fake_mu fake;

void fake_mu_reset(void)
{
    int i;

    for (i = 0; i < FAKE_MAX_THROWS; i++) {
        fake.pts[i] = NULL;
        fake.ms[i] = 0;
    }
    fake.queued = 0;
    fake.hour = 10;
    fake.throws_taken = 0;
    fake.alerts = 0;
    fake.last_pt[0] = '\0';
    fake.last_level = 0;
}

void fake_throw(const char *pt, int ms)
{
    if (fake.queued >= FAKE_MAX_THROWS)
        return;
    fake.pts[fake.queued] = pt;
    fake.ms[fake.queued] = ms;
    fake.queued++;
}

int mu_next_throw(char *pt, int n, int *ms)
{
    const char *p;

    if (fake.throws_taken >= fake.queued)
        return -1;
    p = fake.pts[fake.throws_taken];
    *ms = fake.ms[fake.throws_taken];
    fake.throws_taken++;

    if (p == NULL || (int)strlen(p) >= n)
        return -1;
    memcpy(pt, p, strlen(p) + 1);
    return 0;
}

void mu_alert(const char *pt, int level)
{
    fake.alerts++;
    fake.last_level = level;
    snprintf(fake.last_pt, sizeof fake.last_pt, "%s", pt);
}

int mu_hour(void)
{
    return fake.hour;
}
