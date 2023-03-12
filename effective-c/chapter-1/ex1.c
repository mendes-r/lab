#include<stdlib.h>
#include<stdio.h>

unsigned int *counter_ptr;

int retrieve()
{
  printf("Memory location: %p\n", (void *) counter_ptr);
  return *counter_ptr;
}

void increment(void){
  static unsigned int counter = 0;
  counter++;
  // This is redundant because the address of counter will always be the same.
  counter_ptr = &counter;
}

int main (void){
  int counter;
  for (int i = 0; i < 5; i++){
    increment();
    counter = retrieve();
    printf("Counter value: %d\n\n", counter);
  }
  return 0;
}
