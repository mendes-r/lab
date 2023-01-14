#include <stdlib.h>
#include <stdio.h>

//char *file_path = "data/red-circle.svg";
char *file_path = "data/hello.txt";
long file_length;
char *buffer;

int main()
{
    FILE *p_file;
    p_file = fopen(file_path, "rb");
    fseek(p_file, 0, SEEK_END);
    file_length = ftell(p_file);
    rewind(p_file);

    buffer = (char *) malloc(file_length * sizeof(char));

    fread(buffer, file_length, 1, p_file);
    fclose(p_file);

    printf(buffer);
    free(buffer);

    return 0;
}


