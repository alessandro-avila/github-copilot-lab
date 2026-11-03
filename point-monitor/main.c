/*
 * main.c - main loop of the point machine monitor
 */
#include <stdio.h>

#include "monitor.h"

int main(void)
{
    int steps = 0;

    monitor_init();
    printf("monitor: start\n");
    while (steps < 100) {         /* the real monitor never stops */
        if (monitor_step() == 0)
            break;                /* no more throws */
        steps++;
    }
    printf("monitor: stop after %d throws\n", steps);
    return 0;
}
