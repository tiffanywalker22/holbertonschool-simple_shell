#include "main.h"

/**
 * slash_processor - takes input and removes bin to find command
 * example - /bin/ls becomes ls
 *
 * @slasher: input string to find command
 *
 * Return: returns a string in command form
 */
char *slash_processor(char *slasher)
{
	char **tokenizedList;
	char *finalCom = NULL, *tokenizer;
	char *inputString = strdup(slasher);
	int i = 0, tokenSize = 10;

	tokenizedList = malloc(tokenSize * sizeof(char *));
	if (tokenizedList == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tokenizer = strtok(inputString, " /\n\t\r");
	while (tokenizer != NULL)
	{
		if (i >= tokenSize - 1) /* Check if we need to resize the array */
		{
			tokenSize *= 2;
			tokenizedList = realloc(tokenizedList, tokenSize * sizeof(char *));
			if (tokenizedList == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		tokenizedList[i] = strdup(tokenizer);
		i++;
		tokenizer = strtok(NULL, " ");
	}
	tokenizedList[i] = NULL;
	for (i = 0; tokenizedList[i] != NULL; i++)
	{
		if (tokenizedList[i + 1] == NULL)
			finalCom = strdup(tokenizedList[i]);
		free(tokenizedList[i]);
	}
	free(tokenizedList);
	free(inputString);

	return (finalCom);
}
/**
* get_paths - getting all potential paths
*
* @envp: environmental variables input
* Return: returns array of strings of path
*/
char **get_paths(char **envp)
{
	int i, tokenSize = 20;
	char **paths = NULL;
	char *token = NULL, *pathline = NULL;

	paths = NULL;
	paths = (malloc(tokenSize * sizeof(char *)));
	if (paths == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < tokenSize; i++)
	{
		paths[i] = NULL;
	}
	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH", strlen("PATH")) == 0
		&& envp[i][strlen("PATH")] == '=')
			pathline = envp[i] + strlen("PATH") + 1;
	}
	paths[0] = strdup("/bin");
	paths[1] = strdup("./");
	paths[2] = strdup("../");
	paths[3] = strdup("../../");
	if (pathline != NULL)
	{
		token = strtok(pathline, ":");
		for (i = 4; token != NULL; i++)
		{
			paths[i] = strdup(token);
			token = strtok(NULL, ":");
		}
	}
	return (paths);
}


void check_dir(int *comFlag, char **pathArray,
char *currentArg, char **specificPath)
{
	int j = 0, stopDirFlag = 0;
	DIR *dir;

	for (j = 0, stopDirFlag = 0; pathArray[j] != NULL && stopDirFlag == 0; j++)
	{
		dir = opendir(pathArray[j]);
		if (dir != NULL)
		{
			struct dirent *entry;

			while ((entry = readdir(dir)) != NULL)
			{
				if (strcmp(entry->d_name, currentArg) == 0 ||
				strcmp(currentArg, "exit") == 0
				|| strcmp(currentArg, "env") == 0)
				{
					if (*comFlag < 1)
						*specificPath = strdup(pathArray[j]);
					*comFlag += 1;
					stopDirFlag = 1;
					break;
				}
			}
			closedir(dir);
		}
	}
}

/**
 * get_command - returns commands and subcommands until second command appears
 *
 * @array: array of commands and subcommands
 * @counter: counts how many args to remove from tokenArray
 * @pathArray: Array of all possible paths
 * @specificPath: Path for current path to execute
 *
 * Return: returns an array of strings of command followed by subcommands
 */
char **get_command(char **array, int *counter, char **pathArray,
char **specificPath)
{
	char **command = NULL, *currentArg = NULL; /* BIN_DIR_PATH[256] = "/bin"; */
	int i = 0, tokenSize = 10, comFlag = 0, comCounter = 0;
	/* DIR *dir; */

	command = malloc(tokenSize * sizeof(char *));
	if (command == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (array[i] && comFlag < 2)
	{
		if (array[i][0] == '/' || array[i][0] == '.')
			currentArg = slash_processor(array[i]);
		else
			currentArg = strdup(array[i]);
		check_dir(&comFlag, pathArray, currentArg, specificPath);
		if (comFlag <= 1) /* Copy the command and arguments to the command array */
		{
			if (comCounter == 0)
				command[i] = strdup(currentArg);
			else
				command[i] = strdup(array[i]);
			command[i + 1] = NULL; /* Set the last element to NULL */
			*counter += 1, comCounter += 1;
		}
		i++;
		free(currentArg);
		currentArg = NULL;
	}
	return (command);
}

/**
 * tokenArraySub - subtract tokens from the front of tokenArray
 *
 * @array: temp storage for tokenArrayS
 * @counter: count of how many tokens to take off
 * @flag: Flag that tells program to stop
 *
 * Return: the stored token
 */

char **tokenArraySub(char **array, int *counter, int *flag)
{
	char **temp = NULL;
	int i = 0, j = 0;
	int tokenSize = 10;

	temp = malloc((tokenSize) * sizeof(char *));

	if (temp == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	i = *counter;
	*flag -= *counter;
	if (array[i] == NULL)
	{
		free(temp);
		return (array);
	}
	for (; array[i] != NULL; i++, j++)
	{
		temp[j] = strdup(array[i]);
		if (temp[j] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	temp[j] = NULL;

	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);

	*counter = 0;
	return (temp);
}
