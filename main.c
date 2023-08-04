#include "main.h"

/**
 * argv_path - This is the argv version of shell
 *
 * @argv: array of arguments given on command line
 * @argc: count of argv
 * @tokenArray: Array where each token will be stored
 * @command: Array where current command to execute will be stored
 * @envp: environmental variables input
 */
void argv_path(char **tokenArray, char **command,
int argc, char **argv, char **envp)
{
	int flag = 1, i = 0, nonInterFlag = 0, arrayrmcnt = 0;
	char **pathArray = NULL, *specificPath = NULL;

	pathArray = get_paths(envp);

	while (flag)
	{
		if (nonInterFlag < 1)
		{
			tokenArray = argv_tokenize(argc, argv), nonInterFlag = 1;
			flag = (argc - 1);
		}

		command = get_command(tokenArray, &arrayrmcnt, pathArray, &specificPath);
		tokenArray = tokenArraySub(tokenArray, &arrayrmcnt, &flag);

		forkfunc(command, specificPath, envp);

		for (i = 0; command[i] != NULL; i++)
			free(command[i]);
		free(command);
		free(specificPath);
		if (flag == 0)
		{
			for (i = 0; tokenArray[i]; i++)
			{
				free(tokenArray[i]);
			}
			for (i = 0; pathArray[i]; i++)
				free(pathArray[i]);
			free(pathArray);
			free(tokenArray);
			exit(EXIT_SUCCESS);
		}
	}
}

/**
 * non_inter_path - This is the non interactive version of shell
 *
 * @tokenArray: Array where each token will be stored
 * @command: Array where current command to execute will be stored
 * @buffer: Where the input from stdin will be stored
 * @envp: environmental variables input
 */
void non_inter_path(char **tokenArray, char **command,
char *buffer, char **envp)
{
	int flag = 1, i = 0, nonInterFlag = 0, arrayrmcnt = 0;
	char **pathArray = NULL, *specificPath = NULL;

	pathArray = get_paths(envp);
	while (flag)
	{
		if (nonInterFlag < 1)
		{
			buffer = get_input_non_inter();
			nonInterFlag = 1;
			if (buffer == NULL)
			{
			exit(0);
			}
			tokenArray = gettokens(buffer, &flag, pathArray);
			if (tokenArray == NULL)
				exit(EXIT_SUCCESS);
		}
		command = get_command(tokenArray, &arrayrmcnt, pathArray, &specificPath);
		if (!command[0] || (strcmp(command[0], "exit") == 0))
			normalExit(command, tokenArray, buffer, pathArray);
		tokenArray = tokenArraySub(tokenArray, &arrayrmcnt, &flag);
		forkfunc(command, specificPath, envp);
		for (i = 0; command[i] != NULL; i++)
			free(command[i]);
		free(command);
		free(specificPath);
		if (flag == 0)
		{
			free(buffer);
			for (i = 0; tokenArray[i]; i++)
				free(tokenArray[i]);
			free(tokenArray);
			for (i = 0; pathArray[i]; i++)
				free(pathArray[i]);
			free(pathArray);
			exit(EXIT_SUCCESS);
		}
	}
}

/**
 * interactive_path - This is the interactive version of shell
 *
 * @tokenArray: Array where each token will be stored
 * @command: Array where current command to execute will be stored
 * @buffer: Where the input from stdin will be stored
 * @envp: environmental variables input
 */

void interactive_path(char **tokenArray, char **command,
char *buffer, char **envp)
{
	int flag = 1, i = 0, arrayrmcnt = 0, newInputFlag = 0;
	char **pathArray = NULL, *specificPath = NULL;

	signal(SIGINT, sigintCall);
	pathArray = get_paths(envp);
	while (true)
	{
		if (newInputFlag < 1)
		{
			printf("%s\n", PROMPT);
			buffer = get_input_inter();
			newInputFlag = 1;
			if (buffer == NULL)
				exit(0);
			tokenArray = gettokens(buffer, &flag, pathArray);
			if (tokenArray == NULL)
				exit(EXIT_SUCCESS);
		}
		command = get_command(tokenArray, &arrayrmcnt, pathArray, &specificPath);
		if (!command[0] || (strcmp(command[0], "exit") == 0))
			normalExit(command, tokenArray, buffer, pathArray);
		tokenArray = tokenArraySub(tokenArray, &arrayrmcnt, &flag);
		forkfunc(command, specificPath, envp);
		for (i = 0; command[i] != NULL; i++)
			free(command[i]);
		free(command);
		free(specificPath);
		if (flag == 0)
		{
			free(buffer);
			for (i = 0; tokenArray[i]; i++)
				free(tokenArray[i]);
			free(tokenArray);
			newInputFlag = 0, arrayrmcnt = 0;
		}
	}
}


/**
 * main - THIS FUNCTION FUNCTIONS
 *
 * @argc: count of arguments given
 * @argv: array of arguments given
 * @envp: environmental variables input
 *
 * Return: 0 on success
*/

int main(int argc, char **argv, char **envp)
{
	char *buffer = NULL;
	char **tokenArray = NULL, **command = NULL;
	int isInteractive = 0;

	isInteractive = isatty(STDIN_FILENO);
	if (argc > 1) /* ARGV Non-Interactive */
		argv_path(tokenArray, command, argc, argv, envp);
	else if (argc == 1 && isInteractive == 0) /* Non interactivbe */
		non_inter_path(tokenArray, command, buffer, envp);
	else /* Interactive */
		interactive_path(tokenArray, command, buffer, envp);
	return (0);
}
