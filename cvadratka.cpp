#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
// TODO отдельные файлы

enum AmountRoots 
{
    INFINITY_ROOTS = -2, 
    NULL_ROOTS = 0, 
    ONE_ROOT = 1, 
    TWO_ROOTS = 2, 
    TWO_SAME_ROOTS = -1
};

enum Status 
{
    SUCCESS = 0, 
    ERROR = 1
};

enum Compare 
{
    MORE = 1, 
    LESS = -1, 
    EQUAL = 0
};

const double EPS = 1e-5;
const int COEFF_ARRAY_SIZE = 3;

struct Coefficient
{
    double value = NAN;
    char letter = 'x';
};

struct Roots
{
    double x1 = NAN; 
    double x2 = NAN; 
};

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

const int testsAmount = sizeof(TESTS)/sizeof(TESTS[0]);

int compareToZero (double coefficient);
int scanNumber (Coefficient *coefficient);
int enterNumbers (Coefficient coefficient []);
int printRoots (Coefficient coefficient [], Roots *roots);
int solveLinear (Coefficient coefficient [], struct Roots *roots);
int solveQuadratic (Coefficient coefficient [], struct Roots *roots);
int solve (Coefficient coefficient [], struct Roots *roots);
int printBadTestResults(struct AllValues);
int printGoodTestResults(Roots roots, Test test);
int checkTestResults(struct AllValues);
int test (Test test);

int main ()
{
    Coefficient coefficient [COEFF_ARRAY_SIZE] = { {NAN, 'a'}, {NAN, 'b'}, {NAN, 'c'} };
    Roots roots = {NAN, NAN};

    printf ("Введите \"t\", если хотите запустить тесты, \n");
    printf ("или введите \"s\", если хотите ввести коэффициенты вручную.\n");

    char letter = 'x';
    if (scanf ("%c", &letter) == 1 && (letter == 't' || letter == 'T' || letter == 's' || letter == 'S'))
    {
        if (letter == 't' || letter == 'T')
        {
            for (int i = 0; i < testsAmount; i++)
            test (TESTS [i]);

            return 0;
        }
        else
        {
            if (enterNumbers(coefficient) != SUCCESS) 
            {
                return ERROR;
            }
    
            printRoots (coefficient, &roots);
        }
    }
    else 
    {
        while (getchar () != '\n') {}
        printf ("Ошибка ввода");
        return SUCCESS;
    }
}

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

int scanNumber (Coefficient *coefficient)
{
    printf ("Введите %c:", (*coefficient).letter);
    if (scanf ("%lf", &(*coefficient).value) != 1) 
    {
        while (getchar () != '\n') {}
        printf ("Ошибка ввода\n");
        return ERROR;
    }
    return SUCCESS;
}

int enterNumbers (Coefficient coefficient [])
{
    for (int i = 0; i < COEFF_ARRAY_SIZE; i++) 
    {
       if (scanNumber (&coefficient[i]) != SUCCESS) 
        {
            return ERROR;
        } 
    }

    return SUCCESS;
}

int printRoots (Coefficient coefficient [], Roots *roots) 
{
    switch (solve (coefficient, roots)) 
    {
        case INFINITY_ROOTS: 
            printf ("Бесконечное количество корней\n");
            break;

        case NULL_ROOTS: 
            printf ("Нет корней\n");
            break;

        case ONE_ROOT: 
            printf ("Один корень \nx1 = %lf\n", (*roots).x1);
            break;
        
        case TWO_ROOTS: 
            printf ("Два корня \nx1 = %lf, x2 = %lf\n", (*roots).x1, (*roots).x2);
            break;

        case TWO_SAME_ROOTS: 
            printf ("Два одинаковых корня \nx1 = x2 = %lf\n", (*roots).x1);
            break;

        default: 
            return ERROR;
    }
    return SUCCESS;
}

int solveLinear (Coefficient coefficient [], struct Roots *roots) 
{
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
   if (compareToZero (coefficient[0].value) == EQUAL) 
   {
        return solveLinear (coefficient, roots);

   } 
   else 
   {
        return solveQuadratic (coefficient, roots);
   } 
}

int printBadTestResults(Roots roots, Test test) 
{
    
    printf ("Error Test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d \nExpected: x1 = %lg, x2 = %lg, \
             nRoots = %d\n", test.number, test.coefficient[0].value, test.coefficient[1].value, test.coefficient[2].value,
             roots.x1, roots.x2, solve (test.coefficient, &roots), test.x1Expected, test.x2Expected, test.nRootsExpected);
    return SUCCESS;
}

int printGoodTestResults(Roots roots, Test test) 
{
    
    printf ("Test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d\n", test.number, test.coefficient[0].value,
            test.coefficient[1].value, test.coefficient[2].value, roots.x1, roots.x2, solve (test.coefficient, &roots));
    return SUCCESS;
}

int checkTestResults(Roots roots, Test test)
{
   switch (solve (test.coefficient, &roots))
    {
        case INFINITY_ROOTS:
        case NULL_ROOTS:
            if (solve (test.coefficient, &roots) != test.nRootsExpected)
            {
                printBadTestResults(roots, test);
            }
            else
            {
                printGoodTestResults(roots, test);
            }
            return SUCCESS;

        case ONE_ROOT:
            // TODO check isnan and isinf
            // TODO write function to check if xn is equal to xnExpected
            if (solve (test.coefficient, &roots) != test.nRootsExpected || compareToZero(roots.x1 - test.x1Expected) != EQUAL)
            {
                printBadTestResults(roots, test);
            }
            else
            {
                printGoodTestResults(roots, test);
            }
            return SUCCESS;

        case TWO_ROOTS:
        case TWO_SAME_ROOTS:
            if (solve (test.coefficient, &roots) != test.nRootsExpected || compareToZero(roots.x1 - test.x1Expected) != EQUAL 
                || compareToZero(roots.x2 - test.x2Expected) != EQUAL)
            {
                printBadTestResults(roots, test);
            }
            else
            {
                printGoodTestResults(roots, test);
            }
            return SUCCESS;


        default: 
            return ERROR;
    }
}

int test (Test test) 
{
    double x1 = NAN, x2 = NAN;
    int number = 0;

    Roots roots = {x1, x2};
   
    checkTestResults(roots, test);
    return SUCCESS;
}
