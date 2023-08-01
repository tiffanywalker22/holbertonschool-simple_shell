#include "main.h"

void argv_path(char **tokenArray, char **command, int argc, char **argv)
{
	int flag = 1, i = 0, nonInterFlag = 0, arrayrmcnt = 0;

	printf("This is the argv path\n");
	while (flag)
	{
		if (nonInterFlag < 1)
			{
				tokenArray = argv_tokenize(argc, argv), nonInterFlag = 1;
				flag = (argc - 1);
			}
		for (i = 0; tokenArray[i]; i++)
			printf("Token[%d]: %s\n", i, tokenArray[i]);
		
		command = get_command(tokenArray, &arrayrmcnt);
		tokenArray = tokenArraySub(tokenArray, &arrayrmcnt, &flag);

				for (i = 0; tokenArray[i]; i++)
			printf("tokenArray[%d]: %s\n", i, tokenArray[i]);
		if (command == NULL)
        {
            printf("Command not found in the default path.\n");
        }
		forkfunc(command);
		if (command == NULL)
        {
            printf("Command not found in the default path.\n");
        }
        else
        {
			printf("Got here: else\n");
            for (i = 0; command[i] != NULL; i++)
            {
                printf("command[%d]: %s\n", i, command[i]);
            }
        }
		for (i = 0; command[i] != NULL; i++)
			free(command[i]);
		free(command);
		if (flag == 0)
		{
			for (i = 0; tokenArray[i]; i++)
			{
				free(tokenArray[i]);
			}
			free(tokenArray);
			exit(EXIT_SUCCESS);
		}
	} 
}

void non_inter_path(char **tokenArray, char **command, char *buffer)
{
	int flag = 1, i = 0, nonInterFlag = 0, arrayrmcnt = 0;

	printf("This is the REAL non-interactive path\n");
	while (flag)
	{
		if (nonInterFlag < 1)
		{
			buffer = get_input_mal();
			nonInterFlag = 1;
			printf("Buffer:%s\n", buffer);
			if (buffer == NULL)
			{
			printf("\nReceived Ctrl+D. Exiting the program.\n");
            exit(0);
			}
			tokenArray = gettokens(buffer, &flag);
		}
		for (i = 0; tokenArray[i]; i++)
			printf("Token[%d]: %s\n", i, tokenArray[i]);

		command = get_command(tokenArray, &arrayrmcnt);
		printf("counter: %d\n", arrayrmcnt);
		tokenArray = tokenArraySub(tokenArray, &arrayrmcnt, &flag);
		for (i = 0; tokenArray[i]; i++)
			printf("tokenArray[%d]: %s\n", i, tokenArray[i]);
		if (command == NULL)
        {
            printf("Command not found in the default path.\n");
        }
        else
        {
			printf("Got here: else\n");
            for (i = 0; command[i] != NULL; i++)
            {
                printf("command[%d]: %s\n", i, command[i]);
            }
        }
		forkfunc(command);
		for (i = 0; command[i] != NULL; i++)
			free(command[i]);
		free(command);
		if (flag == 0)
		{
			free(buffer);
			for (i = 0; tokenArray[i]; i++)
				free(tokenArray[i]);
			free(tokenArray);
			exit(EXIT_SUCCESS);
		}
	}
}

void interactive_path(char **tokenArray, char **command, char *buffer)
{
	int flag = 1, i = 0, arrayrmcnt = 0;

	printf("This is the interactive path\n");
	while (flag)
	{
		printf("%s\n", PROMPT);
		buffer = get_input_mal();
		printf("Buffer:%s\n", buffer);
		if (buffer == NULL)
		{
		printf("\nReceived Ctrl+D. Exiting the program.\n");
		exit(0);
		}
		tokenArray = gettokens(buffer, &flag);
		for (i = 0; tokenArray[i]; i++)
			printf("Token[%d]: %s\n", i, tokenArray[i]);

		command = get_command(tokenArray, &arrayrmcnt);
		printf("counter: %d\n", arrayrmcnt);
		tokenArray = tokenArraySub(tokenArray, &arrayrmcnt, &flag);

		for (i = 0; tokenArray[i]; i++)
			printf("tokenArray[%d]: %s\n", i, tokenArray[i]);
		if (command == NULL)
        {
            printf("Command not found in the default path.\n");
        }
        else
        {
			printf("Got here: else\n");
            for (i = 0; command[i] != NULL; i++)
            {
                printf("command[%d]: %s\n", i, command[i]);
            }
        }
		forkfunc(command);
		free(buffer);
		for (i = 0; tokenArray[i]; i++)
			free(tokenArray[i]);
		free(tokenArray);
		for (i = 0; command[i] != NULL; i++)
			free(command[i]);
		free(command);
	}
}


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
	/*int flag = 1, i = 0, nonInterFlag = 0, arrayrmcnt = 0, isInteractive = 0; */
	char *buffer = NULL;
	char **tokenArray = NULL, **command = NULL;
	int isInteractive;

	isInteractive = isatty(STDIN_FILENO);
	printf("Is Interactive: %d\n", isInteractive);
	signal(SIGINT, sigintCall);
	if (argc > 1) /* ARGV Non-Interactive */
		argv_path(tokenArray, command, argc, argv);
	else if (argc == 1 && isInteractive == 0) /* Non interactivbe */
		non_inter_path(tokenArray, command, buffer);
	else /* Interactive */
		interactive_path(tokenArray, command, buffer);
	/*{
		printf("%s\n", PROMPT);
		buffer = get_input_mal();
		printf("Buffer:%s\n", buffer);
		if (buffer == NULL)
		{
		printf("\nReceived Ctrl+D. Exiting the program.\n");
		exit(0);
		}
		tokenArray = gettokens(buffer, &flag);
		if (isInteractive)
			flag = 1;
	}
	for (i = 0; tokenArray[i]; i++)
		printf("Token[%d]: %s\n", i, tokenArray[i]);

	command = get_command(tokenArray, &arrayrmcnt);
	printf("counter: %d\n", arrayrmcnt);
	tokenArray = tokenArraySub(tokenArray, &arrayrmcnt, &flag);

	for (i = 0; tokenArray[i]; i++)
		printf("tokenArray[%d]: %s\n", i, tokenArray[i]);
	if (command == NULL)
	{
		printf("Command not found in the default path.\n");
	}
	else
	{
		printf("Got here: else\n");
		for (i = 0; command[i] != NULL; i++)
		{
			printf("command[%d]: %s\n", i, command[i]);
		}
	}
	forkfunc(command);
	if (argc == 1)
	{
		free(buffer);
		for (i = 0; tokenArray[i]; i++)
			free(tokenArray[i]);
		free(tokenArray);
	}
	else
	{
		if (flag == 0)
		{
			for (i = 0; tokenArray[i]; i++)
			{
				free(tokenArray[i]);
			}
			free(tokenArray);
		}
	} */
					/* Free command */
	/*for (i = 0; command[i] != NULL; i++)
		free(command[i]);
	free(command); */
	return (0);
}
