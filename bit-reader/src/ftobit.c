#include <stdlib.h>
#include <stdio.h>

typedef int unit;
#define bit_per_unit (int)sizeof(unit) * 8

#define one(A, k) (A[(k) / bit_per_unit] |= (1 << ((k) % bit_per_unit)))
#define zero(A, k) (A[(k) / bit_per_unit] &= ~(1 << ((k) % bit_per_unit)))

typedef struct
{
    char *path;
    unsigned long length;
    long counter_size;
} FINFO;

int getBit( int A[],  int k )
{
    return ( (A[k/bit_per_unit] & (1 << (k%bit_per_unit) )) != 0 ) ;     
}


int main(void)
{

}