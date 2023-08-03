#include "main.h"

/**
 * sigintCall - Calls the end of the function with control d or c
 *
 * signal - Signals the call for end of function.
 */

void sigintCall(void)
{

	/* Call Frees if need to */

	exit(0);
}

/**
 * normalExit - Calls the end of the function with input "exit"
 *
 * @command: array of commands to free
 * @tokenArray: array of tokens to free
 * @buffer: frees the string buffer
 * @pathArray: frees the path array
 */
void normalExit(char **command, char **tokenArray,
char *buffer, char **pathArray)
{
	int i = 0;

	/* Call Frees if need to */
	if (command[0])
	{
		for (i = 0; command[i] != NULL; i++)
			free(command[i]);
	}
	free(command);
	free(buffer);
	if (tokenArray[0])
	{
		for (i = 0; tokenArray[i]; i++)
			free(tokenArray[i]);
	}
	free(tokenArray);
	if (pathArray[i])
	{
		for (i = 2; pathArray[i]; i++)
			free(pathArray[i]);
	}
	free(pathArray);

	exit(0);
}
