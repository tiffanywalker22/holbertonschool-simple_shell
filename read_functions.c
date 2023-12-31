#include "main.h"

/**
* get_input_inter - gets input for interactive from stdin
*
* Return: returns input
*/

char *get_input_inter(void)
{
	char *buffer;
	size_t buffSize = BUFF_SIZE;
	ssize_t bytesRead;

	buffer = (char *)malloc(sizeof(char *) * buffSize);
	bytesRead = getline(&buffer, &buffSize, stdin);
	if (bytesRead == -1)
	{
		free(buffer);
		return (NULL);
	}

	if (buffer == NULL)
	{
		free(buffer);
		exit(EXIT_FAILURE);
	}

	return (buffer);
}

/**
 * get_input_non_inter - gets input from stdin, gets every line
 *
 * Return: Returns input from stdin
*/

char *get_input_non_inter(void)
{
	char *buffer = NULL, *all_lines = NULL;
	size_t buffSize = 0;
	ssize_t bytesRead;


	all_lines = (char *)(malloc(sizeof(char *) * BUFF_SIZE));
	if (all_lines == NULL)
	{
		perror("Allocation failed for all_lines");
		exit(EXIT_FAILURE);
	}
	all_lines[0] = '\0';
	/* Reads line by line, adds onto end of one single string (all_lines) */
	while ((bytesRead = getline(&buffer, &buffSize, stdin)) != -1)
	{
		strcat(all_lines, buffer);
	}
	if (bytesRead == -1 && !feof(stdin))
	{
		perror("getline failed");
		free(buffer);
		free(all_lines);
		return (NULL);
	}

	free(buffer);
	return (all_lines);
}

/**
 * gettokens - splits a string into tokens
 *
 * @buffer: temp storage for token
 * @flag: signal to show conditions have been met
 * @pathArray: array of possible paths
 * Return: pointer to first token found, or NULL
 */
char **gettokens(char *buffer, int *flag, char **pathArray)
{
	char *token = NULL, **tokens = NULL;
	int i = 0, tokenSize = 10;

	tokens = malloc(tokenSize * sizeof(char *)), *flag = 0;
	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token = strtok(buffer, " \n\r\t");
	if (!token)
	{
		free(buffer), free(tokens);
		for (i = 0; pathArray[i] != NULL; i++)
			free(pathArray[i]);
		free(pathArray);
		exit(0);
	}
	/* Copy each token into array tokens */
	while (token != NULL)
	{
		tokens[i] = strdup(token), i++, *flag += 1;
		token = strtok(NULL, " \n\r\t");
		if (i >= tokenSize)
		{
			tokenSize *= 2; /* Double the tokenSize if needed */
			tokens = realloc(tokens, tokenSize * sizeof(char *));
			if (tokens == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * argv_tokenize - removes first token of argv
 *
 * @argv: arguments input
 *
 * @argc: count of arguments
 *
 * Return: pointer to array of tokens
 */

char **argv_tokenize(int argc, char **argv)
{
	char **tokens;
	int i;

	tokens = (char **)malloc((argc) * sizeof(char *));
	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	for (i = 1; i < argc; i++)
	{
		tokens[i - 1] = strdup(argv[i]);
		if (tokens[i - 1] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	tokens[argc - 1] = NULL;
	return (tokens);
}
