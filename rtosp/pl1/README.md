# PL1

## 1

### a) and b)

Given that the fork() function is called, there will not be any shared memory between the processes - this, in case of writing into memory.
So, after forking, the child or the parent process will start first. This is outside of our control in this exercise. The OS scheduler is responsible for that. 
There is the possibility of having two tipes of results in the terminal: 

```shell
Step 2. x = -2
Step 3. 77655; x = -2
Step 1. x = 2
Step 3. 0; x = 2

Step 1. x = 2
Step 3. 0; x = 2
Step 2. x = -2
Step 3. 77698; x = -2
```
As we can see the value of variable 'x' is not shared by the two processes.

## 2

### a) 

12 processes will be created

### b)

  fork  - fork  - mescc - fork  - mescc
                                - mescc       
                - mescc - fork  - mescc
                                - mescc
        - fork  - mescc - fork  - mescc
                                - mescc
                - mescc - fork  - mescc
                                - mescc

### c)

12 times.

## 3

### a)

- 'a' is a variable that starts with value 0.
- 'b' is a variable that stores the result of the fork function: 0 if we are the child process, PID of child process if we are the parent process.
- 'c' is a variable that stores the process's PID.
- 'd' is a variable that stores the parent's process PID.

### b)

Here is an example of the output of the code:

```shell
a=5, b=0, c=77867, d=77866
a=5, b=77867, c=77866, d=5235
```

The child process has always a bigger value comparing with the parent's PID.
All processes have a parent.
The value of 'a' is not shared between the processes between they use diferent parts of the memory.

## 4

### a)

16 times.

### b) 

Just change the value 4 in the for-loop to 2.

### c)

See ex4c.c

### d)

NOT DONE

## 5
