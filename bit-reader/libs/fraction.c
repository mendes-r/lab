#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <definition.h>

#include "fraction.h"

CHUNK get_numerator(unsigned int *sequence, unsigned long len);

CHUNK *to_fraction(unsigned int *sequence, unsigned long len)
{
    CHUNK numerator = get_numerator(sequence, len);
    CHUNK denominator = (unsigned long)pow(10, len - 1);

    printf("\n");
    printf("%lu / %lu", numerator, denominator);
    printf("\n");

    return 0;
}

CHUNK get_numerator(unsigned int *sequence, unsigned long len)
{
    CHUNK result = 0;
    CHUNK decimal_place = (unsigned long)pow(10, len - 1);

    for (int i = 0; i < len; i++)
    {
        if (sequence[i] != 0)
            result = result + (sequence[i] * decimal_place);

        decimal_place = decimal_place / 10;
    }

    return result;
}
