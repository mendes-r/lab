#include <stdlib.h>
#include <stdio.h>

// char *file_path = "data/red-circle.svg";
char *file_path = "data/hello.txt";
long file_length;
unsigned char *buffer;

void show_bytes(unsigned char *start, int len);

int main()
{
    FILE *p_file;
    p_file = fopen(file_path, "rb");
    fseek(p_file, 0, SEEK_END);
    file_length = ftell(p_file);
    rewind(p_file);

    buffer = (unsigned char *)malloc(file_length * sizeof(char));

    fread(buffer, file_length, 1, p_file);
    fclose(p_file);

    printf("%s", buffer);
    printf("\n");
    
    show_bytes(buffer, sizeof(file_length * sizeof(char)));

    unsigned int *bits = (unsigned int *)malloc(file_length * 8 * sizeof(unsigned int));
    unsigned int bit = 0;
    long len = file_length * 8;

    for (bit = 0; bit < len; ++bit)
    {
        bits[bit] = ((unsigned int)buffer >> bit) & 1;
    }

    for (bit = len; bit--;)
    {
        printf("%u", bits[bit]);
    }
    printf("\n");

    free(buffer);
    free(bits);

    return 0;
}

void show_bytes(unsigned char *start, int len)
{
    int i;
    for (i = 0; i < len; i++)
    printf("%p\t0x%.2x\n",start+i, *(start+i));
  printf("\n");
}
