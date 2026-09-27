/*
 * checksum.c - check digit of a parcel code
 *
 * The last digit of the code is a check digit (mod 10).
 * Do not touch - it works.
 */
#include <string.h>

#include "checksum.h"

int chk(const char *s)
{
    int i, n, sum = 0, w = 3;

    n = (int)strlen(s);
    if (n < 2 || n > 18)
        return 0;

    for (i = n - 2; i >= 0; i--) {
        if (s[i] < '0' || s[i] > '9')
            return 0;
        sum = sum + (s[i] - '0') * w;
        w = 4 - w;
    }

    if ((10 - sum % 10) % 10 == s[n - 1] - '0')
        return 1;
    return 0;
}
