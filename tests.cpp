#include "tests.h"

int printBadTestResults(Roots roots, Test test) 
{
    assert (!isnan(test.coefficient[0].value));
    assert (!isnan(test.coefficient[1].value));
    assert (!isnan(test.coefficient[2].value));
    
    printf ("Error Test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d \nExpected: x1 = %lg, x2 = %lg,"
            "nRoots = %d\n", test.number, test.coefficient[0].value, test.coefficient[1].value, test.coefficient[2].value,
             roots.x1, roots.x2, solve (test.coefficient, &roots), test.x1Expected, test.x2Expected, test.nRootsExpected);

    return SUCCESS;
}

int printGoodTestResults(Roots roots, Test test) 
{
    assert (!isnan(test.coefficient[0].value));
    assert (!isnan(test.coefficient[1].value));
    assert (!isnan(test.coefficient[2].value));

    printf ("Test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d\n", test.number, test.coefficient[0].value,
            test.coefficient[1].value, test.coefficient[2].value, roots.x1, roots.x2, solve (test.coefficient, &roots));

    return SUCCESS;
}

int checkTestResults(Roots roots, Test test)
{
    assert (!isnan(test.coefficient[0].value));
    assert (!isnan(test.coefficient[1].value));
    assert (!isnan(test.coefficient[2].value));

    if (solve (test.coefficient, &roots) != test.nRootsExpected || (isnan (test.x1Expected) != isnan (roots.x1) ||
        compareToZero(roots.x1 - test.x1Expected) != EQUAL)     || (isnan (test.x2Expected) != isnan (roots.x2) || 
        compareToZero(roots.x2 - test.x2Expected) != EQUAL))
    {
        printBadTestResults(roots, test);
        return ERROR;
    }
    else
    {
        printGoodTestResults(roots, test);
        return SUCCESS;
    }

}

int test (Test test) 
{


    double x1 = NAN, x2 = NAN;

    Roots roots = {x1, x2};
   
    if (checkTestResults(roots, test))
    {
        return ERROR;
    }
    else
    {
        return SUCCESS;
    }
}