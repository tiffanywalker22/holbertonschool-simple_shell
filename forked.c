/**
*forkfunc - forks functions
* @commands: new commands to input
* @specificPath: path for current command
* Return: returns 1 on success
*/


#include "main.h"
int forkfunc(char **commands, char *specificPath, char **envp)
{
	int pid;
	char cmd[1024] = "";

	if (strcmp(commands[0], "env") == 0)
	{
		execute_env(envp);
		return (0);
	}
	strcat(cmd, specificPath);
	strcat(cmd, "/");
	strcat(cmd, commands[0]);
	
	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed");
		return (1);
	}
	else if (pid == 0)
	{
		/* Child process */
		execve(cmd, commands, NULL);
	}
	else
	{
		/* Parent process */
		wait(NULL);
	}
	return (1);
}
