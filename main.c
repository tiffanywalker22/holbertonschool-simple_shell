#include "main.h"

void argv_path(char **tokenArray, char **command, int argc, char **argv)
{
	int flag = 1, i = 0, nonInterFlag = 0, arrayrmcnt = 0;
	char **pathArray = NULL, *specificPath = NULL;

	printf("This is the interactive path\n");
	pathArray = get_paths();

	/* printf("This is the argv path\n"); */
	while (flag)
	{
		if (nonInterFlag < 1)
			{
				tokenArray = argv_tokenize(argc, argv), nonInterFlag = 1;
				flag = (argc - 1);
			}
		/* for (i = 0; tokenArray[i]; i++)
			printf("Token[%d]: %s\n", i, tokenArray[i]); */

		command = get_command(tokenArray, &arrayrmcnt, pathArray, &specificPath);
		tokenArray = tokenArraySub(tokenArray, &arrayrmcnt, &flag);

		/* for (i = 0; tokenArray[i]; i++)
			printf("tokenArray[%d]: %s\n", i, tokenArray[i]); */
		forkfunc(command, specificPath);
		/* if (command == NULL)
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
        } */
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
			for (i = 2; pathArray[i]; i++)
				free(pathArray[i]);
			free(pathArray);
			free(tokenArray);
			exit(EXIT_SUCCESS);
		}
	}
}

void non_inter_path(char **tokenArray, char **command, char *buffer)
{
	int flag = 1, i = 0, nonInterFlag = 0, arrayrmcnt = 0;
	char **pathArray = NULL, *specificPath = NULL;

	printf("This is the interactive path\n");
	pathArray = get_paths();

	/* printf("This is the REAL non-interactive path\n"); */
	while (flag)
	{
		if (nonInterFlag < 1)
		{
			buffer = get_input_non_inter();
			nonInterFlag = 1;
			/* printf("Buffer:%s\n", buffer);  */
			if (buffer == NULL)
			{
			printf("\nReceived Ctrl+D. Exiting the program.\n");
            exit(0);
			}
			tokenArray = gettokens(buffer, &flag);
			if (tokenArray == NULL)
				exit(EXIT_SUCCESS);
		}
		/* for (i = 0; tokenArray[i]; i++)
			printf("Token[%d]: %s\n", i, tokenArray[i]); */

		command = get_command(tokenArray, &arrayrmcnt, pathArray, &specificPath);
		printf("Specific Pathssss: %s", specificPath);
		/* printf("counter: %d\n", arrayrmcnt); */
		tokenArray = tokenArraySub(tokenArray, &arrayrmcnt, &flag);
		/* for (i = 0; tokenArray[i]; i++)
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
        } */
		forkfunc(command, specificPath);
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
			for (i = 2; pathArray[i]; i++)
				free(pathArray[i]);
			free(pathArray);
			exit(EXIT_SUCCESS);
		}
	}
}

void interactive_path(char **tokenArray, char **command, char *buffer)
{
	int flag = 1, i = 0, arrayrmcnt = 0, newInputFlag = 0;
	char **pathArray = NULL, *specificPath = NULL;

	signal(SIGINT, sigintCall);
	printf("This is the interactive path\n");
	pathArray = get_paths();
	while (true)
	{
		printf("\nGoing INNNN3\n");
		if (newInputFlag < 1)
		{
			printf("\nGoing INNNN\n");
			buffer = get_input_non_inter();
			printf("\nGoing INNNN4\n");
			newInputFlag = 1;
			printf("\nGoing INNNN5\n");
			/* printf("Buffer:%s\n", buffer);  */
			if (buffer == NULL)
			{
			printf("\nReceived Ctrl+D. Exiting the program.\n");
            exit(0);
			}
			tokenArray = gettokens(buffer, &flag);
			if (tokenArray == NULL)
				exit(EXIT_SUCCESS);
		}
		printf("\nGoing INNNN2\n");
		for (i = 0; tokenArray[i]; i++)
			printf("Token[%d]: %s\n", i, tokenArray[i]);

		command = get_command(tokenArray, &arrayrmcnt, pathArray, &specificPath);
		printf("counter: %d\n", arrayrmcnt);
		if (!command[0] || (strcmp(command[0], "exit") == 0))
			normalExit(command, specificPath, tokenArray, buffer, pathArray);

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
		forkfunc(command, specificPath);
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
			exit(EXIT_SUCCESS);
			newInputFlag = 0;
		}
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
	/* printf("Is Interactive: %d\n", isInteractive); */
	if (argc > 1) /* ARGV Non-Interactive */
		argv_path(tokenArray, command, argc, argv);
	else if (argc == 1 && isInteractive == 0) /* Non interactivbe */
		non_inter_path(tokenArray, command, buffer);
	else /* Interactive */
		interactive_path(tokenArray, command, buffer);
	return (0);
}
