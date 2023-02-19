#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <fraction.h>

typedef struct FileInfo {
    char *path;
    unsigned long length;
    unsigned long counter_size;
} FileInfo;

unsigned char *open_file(FileInfo *file_info);
unsigned int *get_bits(unsigned char *buffer, FileInfo *file_info);
unsigned int *count_bits(unsigned int *bits, FileInfo *file_info);

void print_array(unsigned int *bits, unsigned long len);

int main()
{
    FileInfo file_info;
    file_info.path = "data/hello1.txt";
    file_info.length = 0;
    file_info.counter_size = 0;

    unsigned char *buffer = open_file(&file_info);
    unsigned int *bits = get_bits(buffer, &file_info);
    unsigned int *sequence = count_bits(bits, &file_info);

    print_array(bits, file_info.length * CHAR_BIT);
    print_array(sequence, file_info.counter_size);

    to_fraction(sequence, file_info.counter_size);

    free(buffer);
    free(bits);
    free(sequence);

    return 0;
}

unsigned char *open_file(FileInfo *file_info)
{
    FILE *p_file = fopen(file_info->path, "rb");

    fseek(p_file, 0, SEEK_END);
    file_info->length = ftell(p_file);
    rewind(p_file);

    unsigned char *buffer = (unsigned char *)malloc(file_info->length * sizeof(char));

    fread(buffer, file_info->length, 1, p_file);
    fclose(p_file);

    return buffer;
}

unsigned int *get_bits(unsigned char *buffer, FileInfo *file_info)
{
    unsigned int *bits = (unsigned int *)malloc(file_info->length * CHAR_BIT * sizeof(unsigned int));
    unsigned int byte_level = 0;

    for (int byte = 0; byte < file_info->length; byte++)
    {
        unsigned char character = buffer[byte];

        for (int bit = 0; bit < CHAR_BIT; bit++)
            bits[byte_level + bit] = (character >> bit) & 1;

        byte_level = byte_level + CHAR_BIT;
    }
    return bits;
}

unsigned int *count_bits(unsigned int *bits, FileInfo *file_info)
{
    unsigned long len = file_info->length * CHAR_BIT;
    unsigned int *sequence = (unsigned int *)malloc(len * sizeof(unsigned int));
    unsigned long count = 0;
    unsigned int previous = bits[0];

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
    return (unsigned int *)realloc(sequence, file_info->counter_size * sizeof(unsigned int));
}

void print_array(unsigned int *bits, unsigned long len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%u", bits[i]);
    }
    printf("\n");   
}

