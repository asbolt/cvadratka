#include "solve.h"

int compareToZero (double coefficient) 
{

    if (coefficient > EPS) 
    {
        return MORE;
    } 
    else if (coefficient < -EPS)
    {
        return LESS;
    }
    else
    {
        return EQUAL;
    }
}

int printRoots (Coefficient coefficient [], Roots *roots) 
{
    assert (!isnan (coefficient[0].value));
    assert (!isnan (coefficient[1].value));
    assert (!isnan (coefficient[2].value));

    switch (solve (coefficient, roots)) 
    {
        case INFINITY_ROOTS: 

            printf ("Бесконечное количество корней\n");
            return SUCCESS;

        case NULL_ROOTS:

            printf ("Нет корней\n");
            return SUCCESS;

        case ONE_ROOT: 

            assert (!isnan((*roots).x1));

            printf ("Один корень \nx1 = %lf\n", (*roots).x1);
            return SUCCESS;
        
        case TWO_ROOTS: 

            assert (!isnan((*roots).x1));
            assert (!isnan((*roots).x2));

            printf ("Два корня \nx1 = %lf, x2 = %lf\n", (*roots).x1, (*roots).x2);
            return SUCCESS;

        case TWO_SAME_ROOTS:

            assert (!isnan((*roots).x1));
            assert (!isnan((*roots).x2));

            printf ("Два одинаковых корня \nx1 = x2 = %lf\n", (*roots).x1);
            return SUCCESS;

        default: 
            return ERROR;
    }
}

int solveLinear (Coefficient coefficient [], struct Roots *roots) 
{
    assert (!isnan (coefficient[0].value));
    assert (!isnan (coefficient[1].value));
    assert (!isnan (coefficient[2].value));

    if (compareToZero (coefficient[1].value) == EQUAL) {

        if (compareToZero (coefficient[2].value) == EQUAL) {

            (*roots).x1 = NAN; 
            (*roots).x2 = NAN;

            return INFINITY_ROOTS;

        } else {

            (*roots).x1 = NAN; 
            (*roots).x2 = NAN;

            return NULL_ROOTS; 
        }

    } else {
        (*roots).x1 = -coefficient[2].value/coefficient[1].value;
        (*roots).x2 = NAN;

        return ONE_ROOT;
    }
}

int solveQuadratic (Coefficient coefficient [], struct Roots *roots)
{
    assert (!isnan (coefficient[0].value));
    assert (!isnan (coefficient[1].value));
    assert (!isnan (coefficient[2].value));

    double D = coefficient[1].value*coefficient[1].value - 4*coefficient[0].value*coefficient[2].value;

    if (compareToZero(D) == LESS)
    {
        (*roots).x1 = NAN; 
        (*roots).x2 = NAN;

        return NULL_ROOTS;
    } 
    else if (compareToZero(D) == EQUAL) 
    {
        (*roots).x1 = -coefficient[1].value/(2*coefficient[0].value);
        (*roots).x2 = -coefficient[1].value/(2*coefficient[0].value);

        return TWO_SAME_ROOTS;
    }
    else
    {
        double d = sqrt(D);
        (*roots).x1 = (-coefficient[1].value + d)/(2*coefficient[0].value);
        (*roots).x2 = (-coefficient[1].value - d)/(2*coefficient[0].value);

        return TWO_ROOTS;
    }
}

int solve (Coefficient coefficient [], Roots *roots)
{ 
    assert (!isnan (coefficient[0].value));
    assert (!isnan (coefficient[1].value));
    assert (!isnan (coefficient[2].value));

    if (compareToZero (coefficient[0].value) == EQUAL) 
    {
        return solveLinear (coefficient, roots);

    } 
    else 
    {
        return solveQuadratic (coefficient, roots);
    } 
}