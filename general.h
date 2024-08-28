#ifndef GENERAL_H_
#define GENERAL_H_

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

struct Roots
{
    double x1 = NAN; 
    double x2 = NAN; 
};

enum AmountRoots 
{
    INFINITY_ROOTS = -2, 
    NULL_ROOTS     = 0, 
    ONE_ROOT       = 1, 
    TWO_ROOTS      = 2, 
    TWO_SAME_ROOTS = -1
};

enum Status 
{
    SUCCESS = 0, 
    ERROR   = 1
};

enum Compare 
{
    MORE  = 1, 
    LESS  = -1, 
    EQUAL = 0
};

#endif