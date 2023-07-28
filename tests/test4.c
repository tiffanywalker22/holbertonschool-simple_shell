#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include<sys/types.h>

int main(void)
{
     char **list = (char **)malloc(4 * sizeof(char *));

    // Initialize each string in the array
    list[0] = strdup("ls");
    list[1] = strdup("-la");
    list[2] = strdup(NULL);


    printf("%s\n", list[0]);

    for (int i = 0; i < 4; i++) {
        free(list[i]);
    }
    free(list);

    return(0);
}