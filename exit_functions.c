#include "main.h"

/**
 * sigintCall - Calls the end of the function with control d or c
 *
 * signal - Signals the call for end of function.
 * @e: input integer from system call
 */

void sigintCall(int e)
{

	/* Call Frees if need to */
	printf("End of Function called: %d", e);
	exit(0);
}

/**
 * normalExit - Calls the end of the function with input "exit"
 *
 * @command: array of commands to free
 * @tokenArray: array of tokens to free
 * @buffer: frees the string buffer
 * @pathArray: frees the path array
 * @specificPath: current path
 */
void normalExit(char **command, char **tokenArray,
char *buffer, char **pathArray, char *specificPath)
{
	int i = 0;

	/* Call Frees if need to */
	if (command[0])
	{
		for (i = 0; command[i] != NULL; i++)
			free(command[i]);
		free(command);
	}
	if (buffer)
		free(buffer);
	if (tokenArray[0])
	{
		for (i = 0; tokenArray[i]; i++)
			free(tokenArray[i]);
		free(tokenArray);
	}
	if (pathArray[i])
	{
		for (i = 0; pathArray[i]; i++)
			free(pathArray[i]);
		free(pathArray);
	}
	free(specificPath);

	exit(0);
}

/**
 * execute_env - shows all environmental variables
 *
 * @envp: environmental variables input
 *
 * Return: returns 0 on success
 */
int execute_env(char **envp)
{
	int i = 0;

	for (i = 0; envp[i]; i++)
	{
		printf("%s\n", envp[i]);
	}
	return (0);
}
