/*
 * mu.h - the monitoring unit next to the points: throw timer, alerts, clock
 */
#ifndef MU_H
#define MU_H

int mu_next_throw(char *pt, int n, int *ms);  /* 0 = a throw, -1 = none */
void mu_alert(const char *pt, int level);     /* 1 = warning, 2 = alarm */
int mu_hour(void);                            /* local time, hour 0-23 */

#endif
