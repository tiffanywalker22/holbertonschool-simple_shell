#include "main.h"
int forkfunc (char **commands)
{
    int pid;
	char cmd[] = "/bin/ls";

	char * list[] = {"ls", NULL};

    pid = fork();
		if (pid < 0) 
		{
			perror("Fork failed");
			return 1;
		} 
		else if (pid == 0)
		{
			/* Child process */
			printf("Child process executing...\n");
			execve(cmd, list, NULL);
			printf("Child process done.\n");
			printf("%s\n", commands[0]);
		} 
		else 
		{
			/* Parent process */
			printf("Parent process waiting for the child...\n");
			wait(NULL); /* Wait for the child process to terminate */
			printf("Parent process done waiting.\n");
		}
		printf("Your pid is: %ld\n", (long int)pid);

	return (1);
}
