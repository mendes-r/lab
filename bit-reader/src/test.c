#include <stdlib.h>
#include <stdio.h>

#define SetBit(A,k)     ( A[(k)/8] |= (1 << ((k)%8)) )
#define ClearBit(A,k)   ( A[(k)/8] &= ~(1 << ((k)%8)) )
#define TestBit(A,k)    ( A[(k)/8] & (1 << ((k)%8)) )

int main()
{
    uint8_t array[2];

    uint8_t result = TestBit(array, 1);

    printf("%d", result);
    printf("\n");

    SetBit(array, 2);

    result = TestBit(array, 2);

    printf("%d", result);
    printf("\n");

    return 0;
}
