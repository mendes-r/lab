#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

unsigned int n_elements = 500;
unsigned int array[n_elements];

int get_max(int start, int end){

  int result = -1;

  for (int i = start; i < end; i++){
    if (array[i] > result)
      result = array[i];
  }

  return result;
}

void main(void){

  
  // initialize array with random numbers from 0-255
  for (int i = 0; i < n_elements; i++)
    array[i] = rand() % 256;

  for (int i = 0; i < 5; i++) {
    int pid = fork();

    if (pid == 0){
      // child process
      int result = get_max(0, 250);
      printf("MAX from pid")

    } else if (pid > 0) {
      // parent process
      // nothing
    } else {
      printf("ERROR");
    }

  }

}
