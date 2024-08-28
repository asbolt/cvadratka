#include "scan.h"
#include "tests.h"

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
    assert (coefficient);

    char letter = 'x';

    if (scanf ("%c", &letter) == 1 && (letter == 't' || letter == 'T' || letter == 's' || letter == 'S'))
    {
        if (letter == 't' || letter == 'T')
        {
            int amountBadBoys = 0;

            for (int i = 0; i < testsAmount; i++)
            {
                amountBadBoys += test (TESTS [i]);
            }
            
            printf ("Количество успешных тестов: %d\n", testsAmount - amountBadBoys);
            printf ("Количество проваленных тестов: %d\n", amountBadBoys);

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
        finishRead ();
        printf ("Ошибка ввода");
        return SUCCESS;
    }
}