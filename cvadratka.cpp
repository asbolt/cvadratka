#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
// TODO отдельные файлы
// TODO выбор тесты или ввод вручную
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


struct Coefficient // TODO default values
{
    double value;
    char letter;
};


struct Roots
{
    double x1; 
    double x2;
    int nRoots; 
};

struct Tests
{
    int number;
    Coefficient coefficient[3];
    double x1Expected; 
    double x2Expected;  
    int nRootsExpected; 
};

const Tests TESTS [] = 
{
    {0, {{1}, {2}, {-3}}, 1, -3, 2}, // d > 0
    {1, {{2}, {4}, {2}}, 1, 1, -1}, // d = 0
    {2, {{4}, {8}, {9}}, NAN, NAN, 0}, // d < 0
    {3, {{0}, {4}, {-8}}, 2, NAN, 1}, // Linear
    {4, {{0}, {0}, {56}}, NAN, NAN, 0}, // NULL
    {5, {{0}, {0}, {0}}, NAN, NAN, -2}, // INF
};

// TODO TESTS_COUNT constant

int compareToZero (double coefficient);
int scanNumber (Coefficient *coefficient);
int enterNumbers (Coefficient coefficient []);
int printRoots (Coefficient coefficient [], Roots *roots);
int solveLinear (Coefficient coefficient [], struct Roots *roots);
int solveQuadratic (Coefficient coefficient [], struct Roots *roots);
int solve (Coefficient coefficient [], struct Roots *roots);
int printTestResults(struct AllValues);
int checkTestResults(struct AllValues);
int test (Tests test);

int main ()
{
    Coefficient coefficient [COEFF_ARRAY_SIZE] = { {NAN, 'a'}, {NAN, 'b'}, {NAN, 'c'} };
    Roots roots = {NAN, NAN, NULL};

    if (enterNumbers(coefficient) != SUCCESS) 
    {
        return ERROR;
    }
    
    printRoots (coefficient, &roots);

    for (int i = 0; i < 5; i++)
    test (TESTS [i]); // TODO tab

    return 0;
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

    if (compareToZero(D) == LESS) // isnan, isinf, isfinite
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

int printTestResults(Roots roots, Tests tests) 
{
    
    printf ("Error Test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d \nExpected: x1 = %lg, x2 = %lg, \
             nRoots = %d\n", tests.number, tests.coefficient[0].value, tests.coefficient[1].value, tests.coefficient[2].value, roots.x1, roots.x2, roots.nRoots,
             tests.x1Expected, tests.x2Expected, tests.nRootsExpected); // TODO keep size of line below 128 symbols
    return SUCCESS;
}

int checkTestResults(Roots roots, Tests tests)
{
    switch (tests.nRootsExpected) // TODO use AmountRoots
    {
        case -2:
        case 0:
            if (roots.nRoots != tests.nRootsExpected)
            {
                printTestResults(roots, tests);
            }
            return SUCCESS;
            break; // TODO break is unused

        case 1: // TODO merge similar 
            // TODO check isnan and isinf
            // TODO write function to check if xn is equal to xnExpected
            if (roots.nRoots != tests.nRootsExpected || compareToZero(roots.x1 - tests.x1Expected) == MORE) // TODO EQUALS
            {
                printTestResults(roots, tests);
            }
            return SUCCESS;
            break;

        case 2:
            if (roots.nRoots != tests.nRootsExpected || compareToZero(roots.x1 - tests.x1Expected) == MORE 
            || compareToZero(roots.x2 - tests.x2Expected) == MORE) // TODO tab
            {
                printTestResults(roots, tests);
            }
            return SUCCESS;
            break;

        case -1:
            if (roots.nRoots != tests.nRootsExpected || compareToZero(roots.x1 - tests.x1Expected) == MORE 
            || compareToZero(roots.x2 - tests.x2Expected) == MORE)
            {
                printTestResults(roots, tests);
            }
            return SUCCESS;
            break;

        default: 
            return ERROR;
    }
}

int test (Tests tests) 
{
    double x1 = NAN, x2 = NAN;
    int number = 0;

    Roots roots = {x1, x2, NULL};

    roots.nRoots = solve (tests.coefficient, &roots);
   
    checkTestResults(roots, tests);
    return SUCCESS;
}
