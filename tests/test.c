#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

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
