#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

char *file_path = "data/hello1.txt";
long file_length;

unsigned char *open_file(char *file_path);
unsigned int *get_bits(unsigned char *buffer);
unsigned int *count_bits(unsigned int *bits, long len);

void print_bits(unsigned int *bits, long len);
void print_intergers(unsigned int *sequence);

int main()
{
    unsigned char *buffer = open_file(file_path);
    unsigned int *bits = get_bits(buffer);
    unsigned int *sequence = count_bits(bits, (file_length * CHAR_BIT));

    print_bits(bits, (file_length * CHAR_BIT));
    print_intergers(sequence);

    free(bits);
    free(buffer);
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

unsigned int *count_bits(unsigned int *bits, long len)
{
    unsigned int sequence[10];
    unsigned int count = 0;
    unsigned int previous = bits[len];

    // define the first type of the first bit count
    printf("%u", previous);

    for (int i = 1; i < len; i++)
    {
        count++;
        if (bits[i] != previous)
        {
            printf("%u", count);
            count = 0;
            previous = bits[i];
        }
    }

    printf("%u", count + 1);

    printf("\n");
    return sequence;
}

void print_bits(unsigned int *bits, long len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%u", bits[i]);
    }
    printf("\n");
}

void print_intergers(unsigned int *sequence)
{
    for (int i = 0; i < 10; i++)
    {
        printf("%u", sequence[i]);
    }
    printf("\n");
}
