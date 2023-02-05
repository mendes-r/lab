#include <stdlib.h>
#include <stdio.h>

char *file_path = "data/hello2.txt";
long file_length;
unsigned char *buffer;

void get_bits(unsigned char *buffer);
void show_memory_location(unsigned char *start, int len);
void show_bits(unsigned int *bits, long len);

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

void get_bits(unsigned char *buffer)
{
    unsigned int *bits = (unsigned int *)malloc(file_length * 8 * sizeof(unsigned int));
    unsigned int bit = 0;
    long len = file_length * 8;

    for (bit = 0; bit < len; ++bit)
    {
        bits[bit] = ((unsigned int)buffer >> bit) & 1;
    }

    show_bits(bits, len);
    free(bits);
}

void show_memory_location(unsigned char *start, int len)
{
    int i;
    for (i = 0; i < len; i++)
        printf("%p\t0x%.2x\n", start + i, *(start + i));
    printf("\n");
}

void show_bits(unsigned int *bits, long len)
{
    unsigned int bit = 0;
    for (bit = len; bit--;)
    {
        printf("%u", bits[bit]);
    }
    printf("\n");
}
