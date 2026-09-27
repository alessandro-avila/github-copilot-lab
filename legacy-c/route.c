/*
 * route.c - finds the chute for a parcel
 *
 * The first two digits of a parcel code are its destination.
 */
#include <stdio.h>
#include <string.h>

#include "route.h"

struct rt {
    char dest[3];
    int chute;
};

/* routing table, extended at runtime by route_add() */
struct rt table[20] = {
    { "10", 1 },
    { "11", 1 },
    { "20", 2 },
    { "30", 3 },
    { "31", 3 },
    { "40", 4 },
};
int nroutes = 6;

int route(const char *code)
{
    int i;

    for (i = 0; i < nroutes; i++) {
        if (strncmp(code, table[i].dest, 2) == 0)
            return table[i].chute;
    }
    printf("route: no route for %.2s, using chute 9\n", code);
    return 9;
}

/* 0 = ok, -1 = table full, -2 = bad destination */
int route_add(const char *dest, int chute)
{
    if (nroutes >= 20)
        return -1;
    if (strlen(dest) != 2)
        return -2;
    memcpy(table[nroutes].dest, dest, 3);
    table[nroutes].chute = chute;
    nroutes++;
    return 0;
}
