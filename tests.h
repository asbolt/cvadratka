#include <solve.h>

#ifndef Roots
    struct Roots
    {
        double x1 = NAN; 
        double x2 = NAN; 
    };
#endif

struct Test
{
    int number = -1;
    Coefficient coefficient[3] = {{NAN, 'x'}, {NAN, 'x'}, {NAN, 'x'}};
    double x1Expected = NAN; 
    double x2Expected = NAN;  
    int nRootsExpected = NULL; 
};

const Test TESTS [] = 
{
    {0, {{1}, {2}, {-3}}, 1, -3, TWO_ROOTS}, // d > 0
    {1, {{2}, {4}, {2}}, -1, -1, TWO_SAME_ROOTS}, // d = 0
    {2, {{4}, {8}, {9}}, NAN, NAN, NULL_ROOTS}, // d < 0
    {3, {{0}, {4}, {-8}}, 2, NAN, ONE_ROOT}, // Linear
    {4, {{0}, {0}, {56}}, NAN, NAN, NULL_ROOTS}, // NULL
    {5, {{0}, {0}, {0}}, NAN, NAN, INFINITY_ROOTS}, // INF
    {6, {{1.678}, {5.829}, {2.443}}, -0.487536,  -2.98624, TWO_ROOTS}, // fractional numbers
};

const int testsAmount = sizeof(TESTS) / sizeof(TESTS[0]);

int printBadTestResults(Roots roots, Test test);
int printGoodTestResults(Roots roots, Test test);
int checkTestResults(Roots roots, Test test);
int test (Test test);
