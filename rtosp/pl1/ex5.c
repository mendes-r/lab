#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PROCESSES 5
#define ELEMENTS 10

int get_max(int chunk, int level, unsigned int *array)
{
  unsigned int result = 0;
  int start = chunk * (level - 1);
  int end = chunk * level;

  for (int i = start; i < end; i++)
    if (array[i] > result)
      result = array[i];

  return result;
}

int main(void)
{
  unsigned int final_result = 0;
  unsigned int chunk = ELEMENTS / PROCESSES;
  unsigned int level = 1;
  unsigned int array[ELEMENTS];
  int processes[PROCESSES];

  // initialize array with random numbers from 0-255
  for (int i = 0; i < ELEMENTS; i++)
  {
    array[i] = rand() % 256;
    printf("%d, ", array[i]);
  }
  printf("\n");

  for (int i = 0; i < PROCESSES; i++)
  {
    int pid = fork();

    if (pid == 0)
    {
      // child process
      int result = get_max(chunk, level, array);
      printf("MAX from pid: %d\n", result);
      exit(result);
    }
    else if (pid > 0)
    {
      // parent process
      processes[i] = pid;
      level++;
    }
  }

  for (int i = 0; i < PROCESSES; i++)
  {
    int wstatus;
    waitpid(processes[i], &wstatus, 0);
    if (WEXITSTATUS(wstatus) > final_result)
      final_result = WEXITSTATUS(wstatus);
  }

  printf("Result: %d\n", final_result);

  return EXIT_SUCCESS;
}
