#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <definition.h>

#include "fraction.h"

uint8_t get_chunk_len();
CHUNK get_numerator(uint8_t *sequence, unsigned long len);
CHUNK get_denominator(unsigned long len);
CHUNK gcf(CHUNK num1, CHUNK num2);
void reduce_fraction(CHUNK numerator, CHUNK denominator);

CHUNK *to_fraction(uint8_t *sequence, long len)
{
    // define chunk max length
    uint8_t chunk_len = get_chunk_len();
    // first bit shows which bit is the first
    // TODO where to store the first bit
    uint8_t *chunk = &sequence[1];

    double result = 0;

    // while loop instead and deal with last bits
    while (chunk_len > 0)
    {
        // prevent smaller numbers that the chunk_len
        if (chunk_len > len)
            chunk_len = len;

        // get numerator and denominator for that chunk
        CHUNK numerator = get_numerator(chunk, chunk_len);
        CHUNK denominator = get_denominator(chunk_len);

        printf("chunk size: %hhu -- ", chunk_len);
        printf("%lu / %lu", numerator, denominator);
        printf(" = %f", numerator / (double)denominator);
        printf("\n");

        result = result + (numerator / (double)denominator);

        chunk = &chunk[chunk_len];
        len = len - chunk_len;

        if (len < chunk_len && len != 0)
            chunk_len = len - 1;
    }
    return 0;
}

void reduce_fraction(CHUNK numerator, CHUNK denominator)
{
    gcf(numerator, denominator);
}

CHUNK gcf(CHUNK num1, CHUNK num2)
{
    return 0;
}

CHUNK get_numerator(uint8_t *sequence, unsigned long len)
{
    CHUNK result = 0;
    CHUNK decimal_place = (CHUNK)pow(10, len - 1);

    for (uint8_t i = 0; i < len; i++)
    {
        if (sequence[i] != 0)
            result = result + (sequence[i] * decimal_place);

        decimal_place = decimal_place / 10;
    }

    return result;
}

CHUNK get_denominator(unsigned long len)
{
    return (CHUNK)pow(10, len);
}

uint8_t get_chunk_len()
{
    double max = pow(2, (sizeof(CHUNK) * 8));
    uint8_t count = 0;

    while (max > 1)
    {
        max = max / 10;
        count++;
    }

    // minus one to prevent overflow
    // TODO improve the above commented problem
    return count - 1;
}
