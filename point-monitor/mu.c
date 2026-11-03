/*
 * mu.c - stand-in for the monitoring unit
 *
 * On site, these functions talk to the monitoring unit next to the
 * points. This version replays eight throws, prints what the unit would
 * send to the maintenance desk and reads the computer's clock, so the
 * program links and runs on a laptop.
 */
#define _CRT_SECURE_NO_WARNINGS   /* MSVC: allow localtime() */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "mu.h"

static const struct {
    const char *pt;   /* points that moved */
    int ms;           /* how long the throw took */
} shift[] = {
    { "P101", 3200 },
    { "P101", 4500 },
    { "P102", 4700 },
    { "P101", 3300 },
    { "P103", 4400 },
    { "P104", 4600 },
    { "P105", 4800 },
    { "P102", 7200 },
};

static int pos = 0;   /* next throw to replay */

int mu_next_throw(char *pt, int n, int *ms)
{
    if (pos >= (int)(sizeof shift / sizeof shift[0]))
        return -1;
    if ((int)strlen(shift[pos].pt) >= n) {
        pos++;
        return -1;
    }
    memcpy(pt, shift[pos].pt, strlen(shift[pos].pt) + 1);
    *ms = shift[pos].ms;
    pos++;
    printf("[mu] points %s moved in %d ms\n", pt, *ms);
    return 0;
}

void mu_alert(const char *pt, int level)
{
    printf("[mu] %s for points %s\n", level == 2 ? "ALARM" : "WARNING", pt);
}

int mu_hour(void)
{
    time_t now = time(NULL);

    return localtime(&now)->tm_hour;
}
