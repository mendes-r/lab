#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include <definition.h>

#include "fraction.h"

uint8_t get_chunk_len();
CHUNK get_numerator(uint8_t *sequence, unsigned long len);
CHUNK get_denominator(unsigned long len);

CHUNK *to_fraction(uint8_t *sequence, long len)
{
    // define chunk max length
    uint8_t chunk_len = get_chunk_len();
    uint8_t *chunk = &sequence[0];

    // while loop instead and deal with last bits
    while(len > 0)
    {
        // get numerator and denominator for that chunk
        CHUNK numerator = get_numerator(chunk, chunk_len);
        CHUNK denominator = get_denominator(chunk_len);

        printf("\n");
        printf("%lu / %lu", numerator, denominator);
        printf("\n");
        printf("%lu", len);
        printf("\n");
        
        len = len - chunk_len;
        chunk = &chunk[chunk_len];

        sleep(1);
    }
    
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
    return (CHUNK)pow(10, len - 1);
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
    
    return count;
}
