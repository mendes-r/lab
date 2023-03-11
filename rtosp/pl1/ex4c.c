#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void main()
{
  int i;
  int status;
  unsigned int pid;

  for (i = 0; i < 2; i++)
  {
    pid = fork();
    if (pid == 0)
    {
      sleep(1); /*sleep(): unistd.h*/
    }
    else if (pid % 2 != 0)
    {
      waitpid(pid, NULL, WSTOPPED);
      printf("Waiting for child to return home. PID= %d\n", pid);
    }
  }
  printf("End of execution!\n");
}
