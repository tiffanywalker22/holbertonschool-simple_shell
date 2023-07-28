#include "main.h"
int forkfunc (char **commands)
{
    int pid;

    pid = fork();
		// printf("You are %d years old.\n", age);
		// printf("Your first buffer is %s.\n", buffer);
		if (pid < 0) 
		{
			perror("Fork failed");
			return 1;
		} 
		else if (pid == 0) 
		{
			// Child process
			printf("Child process executing...\n");
			// Put the child process logic here
			// ...
			/*print_func(buffer); */
            printf("%s\n ", commands[0]);
			printf("Child process done.\n");
		} 
		else 
		{
			// Parent process
			printf("Parent process waiting for the child...\n");
			wait(NULL); // Wait for the child process to terminate
			printf("Parent process done waiting.\n");
		}
		printf("Your pid is: %ld\n", (long int)pid);

	return (1);
}
