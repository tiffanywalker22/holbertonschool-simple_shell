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
	char *buffer;
	char **tokenArray;

	if (!argv || argc < 2)
		printf("No Inputs\n");

	while (flag)
	{
		printf("%s\n", PROMPT);
		buffer = get_input_mal();
		tokenArray = gettokens(buffer);
		free(buffer);

		while (tokenArray[i])
		{
			printf("Token[%d]: %s\n", i, tokenArray[i]);
			i++;
		}

		for (i = 0; tokenArray[i]; i++)
			free(tokenArray[i]);

		free(tokenArray);
		flag = 0;
	}
	return (0);
}
