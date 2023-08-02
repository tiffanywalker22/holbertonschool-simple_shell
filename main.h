#ifndef _MAIN_H_
#define _MAIN_H_

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

#define ERROR_MALLOC -77
#define EXIT_F_STAT -23
#define EXIT_F_ACCESS -24
#define PROMPT "How may I serve you? ;)"
#define WHITESPACE "\n\t\r"
#define PATH_DELIM ":"
#define BUFF_SIZE 1024

/* header includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <stddef.h>

/* function prototypes */

char *get_input_inter(void);
char *get_input_non_inter(void);
char **gettokens(char *buffer, int *flag);
char **get_command(char **array, int *counter);
char **argv_tokenize(int argc, char **argv);
void sigintCall();
int forkfunc (char **commands);
char **tokenArraySub(char **array, int *counter, int *flag);

#endif
