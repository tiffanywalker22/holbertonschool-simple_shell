#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>

char *slash_processor(char *slasher)
{
    char ** tokenizedList;
    char *finalCom = NULL, *tokenizer;
    char *inputString = strdup(slasher);
    int i = 0, tokenSize = 10;

    printf("Bin command recognized: Tokenizing %s", slasher);
    tokenizedList = malloc(tokenSize * sizeof(char*));
    if (tokenizedList == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    tokenizer = strtok(inputString, "/");

    while (tokenizer != NULL)
    {
        if (i >= tokenSize - 1) // Check if we need to resize the array
        {
            tokenSize *= 2;
            tokenizedList = realloc(tokenizedList, tokenSize * sizeof(char*));
            if (tokenizedList == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        tokenizedList[i] = strdup(tokenizer);
        i++;
        tokenizer = strtok(NULL, "/");
    }

    for (i = 0; tokenizedList[i] != NULL; i++)
    {
        if (tokenizedList[i + 1] == NULL)
            finalCom = strdup(tokenizedList[i]);
        printf("%s\n", tokenizedList[i]);
        free(tokenizedList[i]);
    }
    printf("finalCom = %s\n", finalCom);
    free(tokenizedList);

    return (finalCom);
}

char **get_command(char **array)
{
    char **command = NULL, *path, BIN_DIR_PATH[256] = "/bin";
    int i = 0, tokenSize = 10, comFlag = 0;
    DIR *dir;

    command = malloc(tokenSize * sizeof(char*));
    if (command == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    while (array[i] != NULL && comFlag < 2)
    {
        /* If the first character is ‘/’, search only for the last part */
        if (array[i][0] == '/')
            path = slash_processor(array[i]);
        else
            path = strdup(array[i]);
        dir = opendir(BIN_DIR_PATH);
        if (dir != NULL)
        {
            struct dirent *entry;
            printf("%d\n", comFlag);
            while ((entry = readdir(dir)) != NULL)
            {
                if (strcmp(entry->d_name, path) == 0)
                {
                    comFlag ++;
                    printf("Matching command found: %s\n", entry->d_name);
                }
            }
            closedir(dir);
        }
        if (comFlag == 1) /* Copy the command and arguments to the command array */
        {
            printf("Copying array[%d]: %s\n", i, path);
            command[i] = strdup(path);
            command[i + 1] = NULL; /* Set the last element to NULL */
        }
        i++;
    }
    // free(path);
    return command;
}

int main(void)
{
    char *tokenArray[] = {"/usr/bin/ls", "-la", "echo"};
    char **command;
    char *finalCom;
    int i = 0;

    command = get_command(tokenArray);
    // if (command == NULL)
    // {
    //     free(command);
    //     return (-1);
    // }

    for (i = 0; command[i] != NULL; i++)
    {
        printf("Command[%d]: %s\n", i , command[i]);
        free(command[i]);
    }
    free(command);



    return(0);
}