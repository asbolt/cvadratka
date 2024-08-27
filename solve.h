#ifndef SOLVE_H_
#define SOLVE_H_

#include "general.h"

const double EPS = 1e-5;
const int COEFF_ARRAY_SIZE = 3;

struct Coefficient
{
    double value = NAN;
    char letter = 'x';
};

int printRoots (Coefficient coefficient [], Roots *roots);
int solveLinear (Coefficient coefficient [], Roots *roots);
int solveQuadratic (Coefficient coefficient [], Roots *roots);
int solve (Coefficient coefficient [], Roots *roots);
int compareToZero (double coefficient);

#endif