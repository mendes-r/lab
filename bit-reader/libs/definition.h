#ifndef DEFINITION_DOT_H
#define DEFINITION_DOT_H

typedef struct file_info {
    char *path;
    unsigned long length;
    unsigned long counter_size;
} FINFO;

typedef unsigned long CHUNK;
typedef unsigned char BYTE;

#endif /*DEFINITION_DOT_H*/