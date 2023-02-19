#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fraction.h"

unsigned long get_numerator(unsigned int *sequence, unsigned long len);

int *to_fraction(unsigned int *sequence, unsigned long len)
{
    unsigned long numerator = get_numerator(sequence, len);
    unsigned long denominator = (unsigned long)pow(10, len - 1);

    printf("\n");
    printf("%lu / %lu", numerator, denominator);
    printf("\n");

    return 0;
}

unsigned long get_numerator(unsigned int *sequence, unsigned long len)
{
    unsigned long result = 0;
    unsigned long decimal_place = (unsigned long)pow(10, len - 1);

    for (int i = 0; i < len; i++)
    {
        if (sequence[i] != 0)
            result = result + (sequence[i] * decimal_place);

        decimal_place = decimal_place / 10;
    }

    return result;
}
