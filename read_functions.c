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
    int tokenSize = 10; // Initial size for the tokens array

    tokens = malloc(tokenSize * sizeof(char *));

    if (tokens == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(buffer, " ");
    while (token != NULL)
    {
        tokens[i] = strdup(token);
        i++;
        token = strtok(NULL, " ");

        if (i >= tokenSize)
        {
            tokenSize *= 2; // Double the tokenSize if needed
            tokens = realloc(tokens, tokenSize * sizeof(char *));
            if (tokens == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
    }

    tokens = realloc(tokens, (i + 1) * sizeof(char *)); // Resize to actual number of tokens + 1 for NULL

    if (tokens == NULL)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }

    tokens[i] = NULL; // Add NULL as the last element to indicate the end of tokens

    return (tokens);
}






