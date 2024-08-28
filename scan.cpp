#include "scan.h"

int finishRead ()
{
    while (getchar () != '\n') {}

    return SUCCESS;
}

int scanNumber (Coefficient *coefficient)
{
    assert (coefficient);

    printf ("Введите %c:", (*coefficient).letter);
    if (scanf ("%lf", &(*coefficient).value) != 1) 
    {
        finishRead ();
        printf ("Ошибка ввода\n");
        return ERROR;
    }
    return SUCCESS;
}

int enterNumbers (Coefficient coefficient [])
{
    assert (coefficient);

    for (int i = 0; i < COEFF_ARRAY_SIZE; i++) 
    {
       if (scanNumber (&coefficient[i]) != SUCCESS) 
        {
            return ERROR;
        } 
    }

    return SUCCESS;
}