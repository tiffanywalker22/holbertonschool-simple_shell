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
    ssize_t bytesRead;

	buffer = (char *)malloc(sizeof(char *) * buffSize);
	bytesRead = getline(&buffer, &buffSize, stdin);
    if (bytesRead = -1)
    {
        free(buffer);
        return NULL;
    }

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
    int tokenSize = 10; /* Initial size for the tokens array */

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
            tokenSize *= 2; /* Double the tokenSize if needed */
            tokens = realloc(tokens, tokenSize * sizeof(char *));
            if (tokens == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
    }

    /* Resize to actual number of tokens + 1 for NULL */
    tokens = realloc(tokens, (i + 1) * sizeof(char *));

    if (tokens == NULL)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }

    tokens[i] = NULL; /* Add NULL as the last element to indicate the end of tokens */

    return (tokens);
}

/**
 * argv_tokenize - removes first token of argv
 * 
 * argv - arguments input
 * 
 * argc - count of arguments
 * 
 * Returns: pointer to array of tokens
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

/**
 * get_command - gets the first input for a command
 * 
 * @array: array of strings inputted
 * 
 * Return: returns a single character pointer
 */

char *get_command(char **array)
{
    char *command;

    command = array[0];
    printf("%s\n", command);

    return (command);
}





