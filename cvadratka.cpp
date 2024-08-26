#include "scan.h"

int chooseWay (Coefficient coefficient [], Roots roots);

int main ()
{
    Coefficient coefficient [COEFF_ARRAY_SIZE] = { {NAN, 'a'}, {NAN, 'b'}, {NAN, 'c'} };
    Roots roots = {NAN, NAN};

    printf ("Введите \"t\", если хотите запустить тесты, \n");
    printf ("или введите \"s\", если хотите ввести коэффициенты вручную.\n");

    chooseWay (coefficient, roots);
}

int chooseWay (Coefficient coefficient [], Roots roots)
{
    assert(coefficient != NULL);

    char letter = 'x';

    if (scanf ("%c", &letter) == 1 && (letter == 't' || letter == 'T' || letter == 's' || letter == 'S'))
    {
        if (letter == 't' || letter == 'T')
        {
            for (int i = 0; i < testsAmount; i++)
            test (TESTS [i]);

            return SUCCESS;
        }
        else
        {
            if (enterNumbers(coefficient) != SUCCESS) 
            {
                return ERROR;
            }
    
            printRoots (coefficient, &roots);
            return SUCCESS;
        }
    }
    else 
    {
        while (getchar () != '\n') {}
        printf ("Ошибка ввода");
        return SUCCESS;
    }
}