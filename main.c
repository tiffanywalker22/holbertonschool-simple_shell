#include "main.h"

/**
 * main - THIS FUNCTION FUNCTIONS
 *
 * @argc: count of arguments given
 *
 * @argv: array of arguments given
 *
 * Return: 0 on success?
*/

int main(int argc, char **argv)
{
	int flag = 1, i = 0; /*Flag for start/stop */
	char *buffer, *command;
	char **tokenArray;

	while (flag)
	{
		if (argc > 1)
		{
			flag = 0;
			tokenArray = argv_tokenize(argc, argv);
		}
		else
		{
			printf("%s\n", PROMPT);
			buffer = get_input_mal();
			tokenArray = gettokens(buffer);
		}

		for (i = 0; tokenArray[i]; i++)
			printf("Token[%d]: %s\n", i, tokenArray[i]);

		command = get_command(tokenArray);
		printf("%s", command);

		if (argc == 1)
		{
			free(buffer);
			for (i = 0; tokenArray[i]; i++)
				free(tokenArray[i]);
			free(tokenArray);
		}
		else
		{
			for (i = 0; i < argc - 1; i++)
			{
				free(tokenArray[i]);
			}
			free(tokenArray);
		}
		flag = 0;
	}
	return (0);
}
