/*
 * hw.h - sorter hardware: parcel sensor, barcode scanner, diverter, clock
 */
#ifndef HW_H
#define HW_H

#include <time.h>

int hw_parcel_present(void);            /* 1 = a parcel is at the scanner */
int hw_read_barcode(char *buf, int n);  /* 0 = ok, -1 = no read */
void hw_divert(int chute);              /* push the parcel into a chute */
void hw_release(void);                  /* let it run on to the end of the belt */
time_t hw_now(void);                    /* controller clock */

#endif
