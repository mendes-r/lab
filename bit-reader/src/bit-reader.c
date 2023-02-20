#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <fraction.h>
#include <definition.h>

BYTE *open_file(FINFO *file_info);
uint8_t *get_bits(BYTE *buffer, FINFO *file_info);
uint8_t *count_bits(uint8_t *bits, FINFO *file_info);

void print_array(uint8_t *bits, unsigned long len);

int main()
{
    FINFO file_info;
    file_info.path = "data/hello2.txt";
    file_info.length = 0;
    file_info.counter_size = 0;

    BYTE *buffer = open_file(&file_info);
    uint8_t *bits = get_bits(buffer, &file_info);
    uint8_t *sequence = count_bits(bits, &file_info);

    print_array(bits, file_info.length * CHAR_BIT);
    print_array(sequence, file_info.counter_size);

    to_fraction(sequence, file_info.counter_size);

    free(buffer);
    free(bits);
    free(sequence);

    return 0;
}

BYTE *open_file(FINFO *file_info)
{
    FILE *p_file = fopen(file_info->path, "rb");

    fseek(p_file, 0, SEEK_END);
    file_info->length = ftell(p_file);
    rewind(p_file);

    BYTE *buffer = (BYTE *)malloc(file_info->length * sizeof(char));

    fread(buffer, file_info->length, 1, p_file);
    fclose(p_file);

    return buffer;
}

uint8_t *get_bits(BYTE *buffer, FINFO *file_info)
{
    uint8_t *bits = (uint8_t *)malloc(file_info->length * CHAR_BIT * sizeof(uint8_t));
    uint8_t byte_level = 0;

    for (int byte = 0; byte < file_info->length; byte++)
    {
        BYTE character = buffer[byte];

        for (int bit = 0; bit < CHAR_BIT; bit++)
            bits[byte_level + bit] = (character >> bit) & 1;

        byte_level = byte_level + CHAR_BIT;
    }
    return bits;
}

uint8_t *count_bits(uint8_t *bits, FINFO *file_info)
{
    unsigned long len = file_info->length * CHAR_BIT;
    uint8_t *sequence = (uint8_t *)malloc(len * sizeof(uint8_t));
    unsigned long count = 0;
    uint8_t previous = bits[0];

    // define the first type of the first bit count
    sequence[file_info->counter_size] = previous;

    for (int i = 1; i < len; i++)
    {
        count++;
        if (bits[i] != previous)
        {
            file_info->counter_size++;
            sequence[file_info->counter_size] = count;
            count = 0;
            previous = bits[i];
        }
    }

    file_info->counter_size++;
    sequence[file_info->counter_size] = count + 1;
    return (uint8_t *)realloc(sequence, file_info->counter_size * sizeof(uint8_t));
}

void print_array(uint8_t *bits, unsigned long len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%u", bits[i]);
    }
    printf("\n");   
}

