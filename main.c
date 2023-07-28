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
	char **tokenArray; /* **command = NULL;*/


	while (flag)
	{
		signal(SIGINT, sigintCall);
		if (argc > 1)
		{
			flag = 0;
			tokenArray = argv_tokenize(argc, argv);
		}
		else
		{
			printf("%s\n", PROMPT);
			buffer = get_input_mal();
			if (buffer == NULL)
			{
			printf("\nReceived Ctrl+D. Exiting the program.\n");
            exit(0);
			}
			tokenArray = gettokens(buffer);
		}

		for (i = 0; tokenArray[i]; i++)
			printf("Token[%d]: %s\n", i, tokenArray[i]);

		/*command = get_command(tokenArray);
		if (command == NULL)
        {
            printf("Command not found in the default path.\n");
        }
        else
        {
            for (i = 0; command[i] != NULL; i++)
            {
                printf("command[%d]: %s\n", i, command[i]);
            }

            /* Free command
            for (i = 0; command[i] != NULL; i++)
                free(command[i]);
            free(command);
        }*/
	forkfunc(tokenArray);
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
