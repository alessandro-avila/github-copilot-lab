/*
 * test_route.c - tests for route.c (reference solution)
 *
 * One test per scenario in legacy-c/specs/route.spec.md. route_add()
 * changes the global routing table for the rest of the run, so every test
 * that adds a destination puts the number of routes back at the end.
 */
#include "route.h"
#include "test.h"

extern int nroutes;   /* routes in the global table in route.c */

/* Scenario 1 */
static void known_destination_gets_its_chute(void)
{
    CHECK_EQ(3, route("30123458"));
}

/* Scenario 2 - flagged: see spec */
static void destination_without_a_route_gets_chute_9(void)
{
    CHECK_EQ(9, route("55123457"));
}

/* Scenario 3 */
static void added_destination_gets_its_chute(void)
{
    int saved = nroutes;

    CHECK_EQ(0, route_add("50", 5));     /* 0 = ok */
    CHECK_EQ(5, route("50123452"));
    nroutes = saved;
}

/* Scenario 4 - flagged: see spec */
static void adding_an_existing_destination_keeps_the_old_chute(void)
{
    int saved = nroutes;

    CHECK_EQ(0, route_add("30", 7));
    CHECK_EQ(3, route("30123458"));
    nroutes = saved;
}

/* Scenario 5 */
static void table_holds_at_most_20_routes(void)
{
    int saved = nroutes;
    char destination[3] = "60";
    int number;

    for (number = 60; number <= 73; number++) {
        destination[0] = (char)('0' + number / 10);
        destination[1] = (char)('0' + number % 10);
        CHECK_EQ(0, route_add(destination, 6));
    }
    CHECK_EQ(-1, route_add("74", 7));    /* -1 = table full */
    nroutes = saved;
}

/* Scenario 6 */
static void destination_needs_exactly_two_characters(void)
{
    CHECK_EQ(-2, route_add("500", 5));   /* -2 = bad destination */
}

int main(void)
{
    RUN(known_destination_gets_its_chute);
    RUN(destination_without_a_route_gets_chute_9);
    RUN(added_destination_gets_its_chute);
    RUN(adding_an_existing_destination_keeps_the_old_chute);
    RUN(table_holds_at_most_20_routes);
    RUN(destination_needs_exactly_two_characters);
    return TEST_SUMMARY();
}
