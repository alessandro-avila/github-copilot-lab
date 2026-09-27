/*
 * main.c - main loop of the sorting controller
 */
#include <stdio.h>

#include "sorter.h"

int main(void)
{
    int steps = 0;

    sorter_init();
    printf("sorter: start\n");
    while (steps < 50) {          /* the real controller never stops */
        if (sorter_step() == 0)
            break;                /* belt empty */
        steps++;
    }
    printf("sorter: stop after %d steps\n", steps);
    return 0;
}
