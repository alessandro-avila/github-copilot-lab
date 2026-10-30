/*
 * monitor.c - one step of the point machine monitor
 *
 * Takes the next throw from the monitoring unit, grades it and sends an
 * alert to the maintenance desk when the points move too slowly.
 */
#include <stdio.h>

#include "grade.h"
#include "monitor.h"
#include "mu.h"

static int n = 0;   /* slow throws in a row */

void monitor_init(void)
{
    n = 0;
}

int monitor_step(void)
{
    char pt[8];
    int t, g, h;

    if (mu_next_throw(pt, sizeof pt, &t) != 0)
        return 0;

    /* night possession 23:00-03:00: technicians test the points */
    h = mu_hour();
    if (h >= 23 && h < 3)
        return 1;

    g = grade(t);
    if (g == 0) {
        n = 0;
        return 1;
    }
    if (g == 1 && ++n < 3) {
        mu_alert(pt, 1);
        return 2;
    }
    mu_alert(pt, 2);
    printf("monitor: alarm for %s, throw took %d ms\n", pt, t);
    n = 0;
    return 3;
}
