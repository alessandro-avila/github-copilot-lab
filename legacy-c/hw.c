/*
 * hw.c - stand-in for the real hardware
 *
 * On the real sorter these functions talk to the conveyor controller.
 * This version replays four parcels, prints what the hardware would do
 * and uses the computer's clock, so the program links and runs on a laptop.
 */
#include <stdio.h>
#include <string.h>

#include "hw.h"

static const struct {
    const char *label;   /* NULL = label cannot be read */
    int misses;          /* failed reads before a good read */
} belt[] = {
    { "30123458", 0 },   /* normal parcel */
    { "10123454", 2 },   /* read on the third try */
    { NULL, 0 },         /* damaged label */
    { "55123457", 0 },   /* destination 55 */
};

static int pos = 0;      /* parcel at the scanner */
static int reads = 0;    /* reads of that parcel so far */

int hw_parcel_present(void)
{
    return pos < (int)(sizeof belt / sizeof belt[0]);
}

int hw_read_barcode(char *buf, int n)
{
    reads++;
    if (belt[pos].label == NULL || reads <= belt[pos].misses
        || (int)strlen(belt[pos].label) >= n) {
        printf("[hw] scanner: no read\n");
        return -1;
    }
    memcpy(buf, belt[pos].label, strlen(belt[pos].label) + 1);
    printf("[hw] scanner: %s\n", buf);
    return 0;
}

static void next_parcel(void)
{
    pos++;
    reads = 0;
}

void hw_divert(int chute)
{
    printf("[hw] diverter: parcel into chute %d\n", chute);
    next_parcel();
}

void hw_release(void)
{
    printf("[hw] no divert: parcel runs to the end of the belt\n");
    next_parcel();
}

time_t hw_now(void)
{
    return time(NULL);
}
