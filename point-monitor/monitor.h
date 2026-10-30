#ifndef MONITOR_H
#define MONITOR_H

void monitor_init(void);   /* call once at start-up */

/* one step of the monitor, called from the main loop
   returns 0 = no throw, 1 = no alert, 2 = warning, 3 = alarm */
int monitor_step(void);

#endif
