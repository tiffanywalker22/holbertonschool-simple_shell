#include "main.h"

/**
 * sigintCall - Calls the end of the function with control d or c
 * 
 * signal - Signals the call for end of function.
 */

void sigintCall()
{

    /* Call Frees if need to */

    exit(0);
}

void normalExit(char **command, char *specificPath, char **tokenArray,
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
    if (specificPath)
        free(specificPath);
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