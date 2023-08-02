#include "main.h"
int forkfunc (char **commands)
{
    int pid;
	char cmd[256] = "/bin/";

	printf("Commands[0]: %s", commands[0]);
	strcat(cmd, commands[0]);
	/*printf("This is the new cmd: %s\n", cmd); */

	/*for (; commands[i]; i++)
		printf("In the Fork function, Command[%d]: --%s--", i, commands[i]); */

    pid = fork();
		if (pid < 0) 
		{
			perror("Fork failed");
			return 1;
		} 
		else if (pid == 0)
		{
			/* Child process */
			/* printf("Child process executing...\n"); */
			execve(cmd, commands, NULL);
			/* printf("Child process done.\n"); */
			/* printf("%s\n", commands[0]); */
		} 
		else 
		{
			/* Parent process */
			/*printf("Parent process waiting for the child...\n"); */
			wait(NULL); /* Wait for the child process to terminate */
			/*printf("Parent process done waiting.\n");*/
		}
		/*printf("Your pid is: %ld\n", (long int)pid); */

	return (1);
}
