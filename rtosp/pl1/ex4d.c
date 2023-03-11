#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void main()
{
  int i;
  int status;
  int order = 0;
  unsigned int pid;

  for (i = 0; i < 2; i++) 
  {
    order++;
    pid = fork();

    if (pid == 0) 
    {
      sleep(1); /*sleep(): unistd.h*/
      printf("[CHILD] PID = %d. Number of creation order %d\n", getpid(), order);
    }
    else if (pid > 0)
    {
      printf("[PARENT] PID = %d\n", getpid());
      if (pid%2 > 0)
      {
        printf("Waiting for CHILD with PID = %d to return home.\n", pid);
        waitpid(pid);
      }
    }
    else 
    {
      printf("ERROR\n");
    }
  }

  printf("End of execution!\n");
}
