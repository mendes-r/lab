#include <stdlib.h>
#include <stdio.h>

void f_one(void) { printf("Hello, I'm Function 1\n"); }
void f_two(void) { printf("Hello, I'm Function 2\n"); }
void f_three(void) { printf("Hello, I'm Function 3\n"); }

int main(void)
{

  void (*f_ptr[3])(void) = {f_one, f_two, f_three};

  int option;

  printf("\nEnter function number you want");
  printf("\nYou should not enter other than 1, 2 or 3: ");
  scanf("%d", &option);

  (*f_ptr[option - 1])();
}
