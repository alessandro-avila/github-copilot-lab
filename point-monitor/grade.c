/*
 * grade.c - grades one throw of a point machine
 *
 * A throw moves the points from normal to reverse, or back. The
 * monitoring unit times every throw in milliseconds.
 */
#include "grade.h"

/* 0 = ok, 1 = slow, 2 = too slow */
int grade(int t)
{
    if (t > 6000)
        return 2;
    if (t > 4000)
        return 1;
    return 0;
}
