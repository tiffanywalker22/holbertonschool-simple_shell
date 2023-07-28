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
    list[0] = strdup("This");
    list[1] = strdup("is");
    list[2] = strdup("a");
    list[3] = strdup("word");

    printf("%s\n", list[0]);

    for (int i = 0; i < 4; i++) {
        free(list[i]);
    }
    free(list);

    return(0);
}