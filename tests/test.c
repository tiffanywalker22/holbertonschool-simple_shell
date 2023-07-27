#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#define MAX_CMD_LENGTH 100

#define MAX_NUM_PARAMS 10
/**
 * print_func - prints the inputs in a child process
 * age - age to print
 * buffer - buffer to print
*/

void print_func(char *buffer)
{
	printf("Your first buffer is %s.\n", buffer);
}

/**
 * main - prints user input in loops
 * Return: 1 or -1
*/

int main(int argc, char **argv)
{
	/*Declare variables*/
	char *buffer, *token;
	pid_t pid;
	int flag = 1, i = 0;
	size_t len = 1024;
	ssize_t lineSize = 0;

	/*Loop*/
	while (flag)
	{
		/*User Prompt*/
		printf("Hello\nPlease type your first buffer, then press enter\n");

		/*Store user input*/
		buffer = (char *)(malloc(sizeof(char *) * len));
		lineSize = getline(&buffer, &len, stdin);
		printf("You entered %s, which has %zu chars.\n", buffer, lineSize);
		// buffer[] = buffer;

		printf("%s", buffer);

		token = strtok(buffer, " ");
		while (token != NULL)
		{
			printf("Token: %s\n", token);
			token = strtok(NULL, " ");
		}
		// /* If user gives 3 inputs */
		// if (argc > 10)
		// {
		// 	printf("Hey... you did it wrong...\n");
		// 	exit(98);
		// }
		if (buffer == "exit")
			printf("1\n");

		if (strcmp(buffer, "exit") == 0)
		{
			printf("They are equal");
			flag = 0;
			break;
		}

		/*Print answers*/
		pid = fork();
		// printf("You are %d years old.\n", age);
		// printf("Your first buffer is %s.\n", buffer);
		if (pid < 0) 
		{
			perror("Fork failed");
			return 1;
		} 
		else if (pid == 0) 
		{
			// Child process
			printf("Child process executing...\n");
			// Put the child process logic here
			// ...
			print_func(buffer);
			printf("Child process done.\n");
		} 
		else 
		{
			// Parent process
			printf("Parent process waiting for the child...\n");
			wait(NULL); // Wait for the child process to terminate
			printf("Parent process done waiting.\n");
		}
		printf("Your pid is: %ld\n", (long int)pid);

		flag = 0;
		free(buffer);
	}
	return (1);
}
void execArgsPiped(char **argv, int argc)
{
    // Tokenize the input command to extract individual commands and arguments
    char *command;
    char *commands[2];
    int i = 0;
    while ((command = strsep(&input, "|")) != NULL)
    {
        commands[i++] = command;
    }

    // Remove leading and trailing spaces from the commands
    for (int j = 0; j < i; j++)
    {
        char *cmd = commands[j];
        while (*cmd == ' ')
        {
            cmd++;
        }

        char *end = cmd + strlen(cmd) - 1;
        while (*end == ' ' || *end == '\n')
        {
            *end = '\0';
            end--;
        }
        commands[j] = cmd;
    }

    // Create a pipe and fork to handle the commands
    int pipefd[2];
    if (pipe(pipefd) < 0)
    {
        perror("Pipe could not be initialized");
        return;
    }

    pid_t p1 = fork();
    if (p1 < 0)
    {
        perror("Could not fork");
        return;
    }

    if (p1 == 0)
    {
        // Child 1 executing...
        // It only needs to write at the write end
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execlp(commands[0], commands[0], NULL); // Execute the first command
        perror("Could not execute command");
        exit(1);
    }
    else
    {
        // Parent executing
        pid_t p2 = fork();
        if (p2 < 0)
        {
            perror("Could not fork");
            return;
        }

        if (p2 == 0)
        {
            // Child 2 executing...
            // It only needs to read at the read end
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);

            execlp(commands[1], commands[1], NULL); // Execute the second command
            perror("Could not execute command");
            exit(1);
        }
        else
        {
            // parent executing, waiting for two children
            wait(NULL);
            wait(NULL);
            close(pipefd[0]);
            close(pipefd[1]);
        }
    }
}

int main(void)
{
    char input[256];
    printf("Enter command: ");
    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        execArgsPiped(input);
    }
    return 0;
}