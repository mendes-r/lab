#include <stdlib.h>
#include <stdio.h>

typedef int unit;
#define bit_per_unit (int)sizeof(unit) * 8

#define SetBit(A, k) (A[(k) / bit_per_unit] |= (1 << ((k) % bit_per_unit)))
#define ZeroBit(A, k) (A[(k) / bit_per_unit] &= ~(1 << ((k) % bit_per_unit)))

int GetBit( int A[],  int k )
{
    return ( (A[k/bit_per_unit] & (1 << (k%bit_per_unit) )) != 0 ) ;     
}

int main()
{
    printf("Array unit size: %d\n", bit_per_unit);

    unit array[3];

    unit result = TestBit(array, 2);

    printf("Before: %d", result);
    printf("\n");

    SetBit(array, 2);

    result = GetBit(array, 2);

    printf("After: %d", result);
    printf("\n");

    return 0;
}
