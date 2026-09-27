#ifndef SORTER_H
#define SORTER_H

void sorter_init(void);   /* call once at start-up */

/* one step of the controller, called from the main loop
   returns 0 = no parcel, 1 = read again, 2 = sorted, -1 = gave up */
int sorter_step(void);

#endif
