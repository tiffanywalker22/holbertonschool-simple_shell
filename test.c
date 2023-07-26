#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

/**
 * print_func - prints the inputs in a child process
 * age - age to print
 * name - name to print
*/

void print_func(char *name)
{
	printf("Your first name is %s.\n", name);
}

/**
 * main - prints user input in loops
 * Return: 1 or -1
*/

int main(int argc, char **argv)
{
	/*Declare variables*/
	char *name, *token;
	pid_t pid;
	int flag = 1;
	size_t len = 0;
	ssize_t lineSize = 0;

	/*Loop*/
	while (flag)
	{
		/*User Prompt*/
		printf("Hello\nPlease type your first name, then press enter\n");

		/*Store user input*/
		lineSize = getline(&name, &len, stdin);
		printf("You entered %s, which has %zu chars.\n", name, lineSize);

		token = strtok(name, " ");
		while (token != NULL)
		{
			printf("Token: %s\n", token);
			token++;
		}
		// /* If user gives 3 inputs */
		// if (argc > 10)
		// {
		// 	printf("Hey... you did it wrong...\n");
		// 	exit(98);
		// }
		if (name == "exit")
			printf("1\n");

		if (strcmp(name, "exit") == 0)
		{
			printf("They are equal");
			flag = 0;
			break;
		}

		/*Print answers*/
		pid = fork();
		// printf("You are %d years old.\n", age);
		// printf("Your first name is %s.\n", name);
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
			print_func(name);
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
	}
	return (1);
}
