#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

char *file_path = "data/hello1.txt";
long file_length;
unsigned char *buffer;

void get_bits(unsigned char *buffer);
void show_memory_location(unsigned char *start, long len);
void show_bits(unsigned int *bits, long len);
void count_bits(unsigned int *bits, long len);

int main()
{
    FILE *p_file;
    p_file = fopen(file_path, "rb");

    fseek(p_file, 0, SEEK_END);
    file_length = ftell(p_file);
    rewind(p_file);

    buffer = (unsigned char *)malloc(file_length * sizeof(char));

    fread(buffer, file_length, 1, p_file);

    get_bits(buffer);

    fclose(p_file);
    free(buffer);
    return 0;
}

void count_bits(unsigned int *bits, long len)
{
    unsigned int count = 0;
    unsigned int previous = bits[len];
    unsigned int bit;

    for (bit = 1; bit < len; bit++)
    {
        count++;
        if (bits[bit] != previous)
        {
            printf("%u", count);
            count = 0;
            previous = bits[bit];
        }

    }
    printf("\n");
}

void get_bits(unsigned char *buffer)
{
    unsigned int *bits = (unsigned int *)malloc(file_length * CHAR_BIT * sizeof(unsigned int));
    unsigned int byte = 0;
    unsigned int byte_level = 0;

    for (byte = 0; byte < file_length; byte++)
    {
        unsigned char b = buffer[byte];

        for (int bit = 0; bit < CHAR_BIT; bit++)
        {
            printf("%u", (b >> bit) & 1);
            bits[byte_level + bit] = (b >> bit) & 1;
        }

        byte_level = byte_level + CHAR_BIT;
    }
    printf("\n");

    show_bits(bits, (file_length * CHAR_BIT));
    count_bits(bits, (file_length * CHAR_BIT));

    free(bits);
}

void show_memory_location(unsigned char *start, long len)
{
    int i;
    for (i = 0; i < len; i++)
        printf("%p\t0x%.2x\n", start + i, *(start + i));
    printf("\n");
}

void show_bits(unsigned int *bits, long len)
{
    unsigned int bit = 0;
    for (bit = 0; bit < len; bit++)
    {
        printf("%u", bits[bit]);
    }
    printf("\n");
}
