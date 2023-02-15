#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

char *file_path = "data/hello1.txt";
long file_length;
long count_size = 0;

unsigned char *open_file(char *file_path);
unsigned int *get_bits(unsigned char *buffer);
unsigned int *count_bits(unsigned int *bits);

void print_bits(unsigned int *bits);
void print_intergers(unsigned int *sequence);

int main()
{
    unsigned char *buffer = open_file(file_path);
    unsigned int *bits = get_bits(buffer);
    unsigned int *sequence = count_bits(bits);

    print_bits(bits);
    print_intergers(sequence);

    free(buffer);
    free(bits);
    free(sequence);

    return 0;
}

unsigned char *open_file(char *file_path)
{
    FILE *p_file = fopen(file_path, "rb");

    fseek(p_file, 0, SEEK_END);
    file_length = ftell(p_file);

    rewind(p_file);

    unsigned char *buffer = (unsigned char *)malloc(file_length * sizeof(char));

    fread(buffer, file_length, 1, p_file);
    fclose(p_file);

    return buffer;
}

unsigned int *get_bits(unsigned char *buffer)
{
    unsigned int *bits = (unsigned int *)malloc(file_length * CHAR_BIT * sizeof(unsigned int));
    unsigned int byte = 0;
    unsigned int byte_level = 0;

    for (byte = 0; byte < file_length; byte++)
    {
        unsigned char b = buffer[byte];

        for (int bit = 0; bit < CHAR_BIT; bit++)
            bits[byte_level + bit] = (b >> bit) & 1;

        byte_level = byte_level + CHAR_BIT;
    }
    return bits;
}

unsigned int *count_bits(unsigned int *bits)
{
    int len = file_length * CHAR_BIT;

    unsigned int *sequence = (unsigned int *)malloc(len  * sizeof(unsigned int));
    unsigned int count = 0;
    unsigned int previous = bits[len];

    // define the first type of the first bit count
    printf("%u", previous);
    sequence[count_size] = previous;

    for (int i = 1; i < len; i++)
    {
        count++;
        if (bits[i] != previous)
        {
            count_size ++;
            printf("%u", count);
            sequence[count_size] = count;
            count = 0;
            previous = bits[i];
        }
    }

    count_size ++;
    sequence[count_size] = count;

    printf("%u", count + 1);
    printf("\n");

    printf("%ld", count_size);
    printf("\n");

    sequence = realloc(sequence, count_size);

    return sequence;
}

void print_bits(unsigned int *bits)
{
    int len = file_length * CHAR_BIT;

    for (int i = 0; i < len; i++)
    {
        printf("%u", bits[i]);
    }
    printf("\n");
}

void print_intergers(unsigned int *sequence)
{
    printf("%ld", count_size);
    printf("\n");

    for (int i = 0; i < count_size; i++)
    {
        printf("%u", sequence[i]);
        printf("/");
    }
    printf("\n");
}
