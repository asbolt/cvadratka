#include "scan.h"

int scanNumber (Coefficient *coefficient)
{
    assert(coefficient != NULL);

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
    assert(coefficient != NULL);

    for (int i = 0; i < COEFF_ARRAY_SIZE; i++) 
    {
       if (scanNumber (&coefficient[i]) != SUCCESS) 
        {
            return ERROR;
        } 
    }

    return SUCCESS;
}