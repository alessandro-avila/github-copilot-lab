/*
 * sorter.c - one step of the sorting controller
 *
 * Reads the parcel at the scanner and diverts it into its chute.
 */
#include <stdio.h>

#include "checksum.h"
#include "hw.h"
#include "route.h"
#include "sorter.h"

static int tries = 0;   /* failed reads */

void sorter_init(void)
{
    tries = 0;
}

int sorter_step(void)
{
    char code[20];
    int chute, hour;

    if (!hw_parcel_present())
        return 0;

    if (hw_read_barcode(code, sizeof code) != 0 || !chk(code)) {
        tries++;
        if (tries < 5)
            return 1;
        printf("sorter: giving up after %d reads\n", tries);
        hw_release();
        tries = 0;
        return -1;
    }

    chute = route(code);

    /* trucks leave at 18:00, late parcels wait for tomorrow */
    hour = (int)(hw_now() / 3600 % 24);
    if (hour >= 18)
        chute = 8;

    hw_divert(chute);
    printf("sorter: %s -> chute %d\n", code, chute);
    return 2;
}
