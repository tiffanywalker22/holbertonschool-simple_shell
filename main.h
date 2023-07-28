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

/* function prototypes */

char *get_input_mal(void);
char **gettokens(char *buffer);
char *get_command(char **array);
char **argv_tokenize(int argc, char **argv);
void sigintCall(int signal);

#endif
