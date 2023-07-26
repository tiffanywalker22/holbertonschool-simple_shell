#include "main.h"

/**
 * get_input_mal - gets input from stdin
 *
 * Return: Returns input from stdin
*/

char *get_input_mal(void)
{
	char *buffer;
	size_t buffSize = BUFF_SIZE;

	buffer = (char *)malloc(sizeof(char *) * buffSize);
	getline(&buffer, &buffSize, stdin);

	if (buffer == NULL)
	{
		free(buffer);
		exit(EXIT_FAILURE);
	}

	return (buffer);
}

/**
 * strtok - splits a string into tokens
 *
 * Return: pointer to first token found, or NULL
 */
char **gettokens(char *buffer)
{
	char *token;
	char **tokens = NULL;
	int i = 0;

	token = strtok(buffer, " ");
	while (token != NULL)
	{
		if (i == 0)
			tokens = malloc(sizeof(char *));
		else
			tokens = realloc(tokens, (i + 1) * sizeof(char *));
		tokens[i] = strdup(token);
		i++;
		token = strtok(NULL, " ");
	}
		free(token);

return (tokens);
}
