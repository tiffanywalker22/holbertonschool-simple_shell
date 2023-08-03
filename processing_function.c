#include "main.h"

/**
 * slash_processor - takes input and removes bin to find command
 * example - /bin/ls becomes ls
 * 
 * @slasher: input string to find command
 * 
 * Return: returns a string in command form
 */
char *slash_processor(char *slasher)
{
    char ** tokenizedList;
    char *finalCom = NULL, *tokenizer;
    char *inputString = strdup(slasher);
    int i = 0, tokenSize = 10;

    /* ./hshprintf("Bin command recognized: Tokenizing %s", slasher); */
    tokenizedList = malloc(tokenSize * sizeof(char*));
    if (tokenizedList == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    tokenizer = strtok(inputString, " /\n\t\r");

    while (tokenizer != NULL)
    {
        if (i >= tokenSize - 1) /* Check if we need to resize the array */
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
        tokenizer = strtok(NULL, " ");
    }
    tokenizedList[i] = NULL;

    for (i = 0; tokenizedList[i] != NULL; i++)
    {
        if (tokenizedList[i + 1] == NULL)
            finalCom = strdup(tokenizedList[i]);
        /* printf("%s\n", tokenizedList[i]); */
        free(tokenizedList[i]);
    }
    /*printf("finalCom = %s\n", finalCom); */
    free(tokenizedList);
    free(inputString);

    return (finalCom);
}
/*
* get_paths - getting all potential paths
*
*/
char **get_paths(void)
{
    extern char **environ;
    int i, tokenSize = 20;
    char **paths = NULL;
    char *token = NULL, *pathline = NULL;

    paths = (malloc(tokenSize * sizeof(char *)));
    if (paths == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], "PATH", strlen("PATH")) == 0 && environ[i][strlen("PATH")] == '=')
            pathline = environ[i] + strlen("PATH") + 1;
    }
    token = strtok(pathline, ":");
    printf("token: %s\n", token);
    paths[0] = "/bin";
    paths[1] = "/";
    for (i = 2; token!= NULL; i++)
    {
        paths[i] = strdup(token);
        token = strtok(NULL, ":");
    }
    for (i = 0; paths[i] != NULL; i++)
        printf("paths[%d]: %s\n", i, paths[i]);

    free(token);
    return(paths);
}

/**
 * get_command - returns commands and subcommands until second command appears
 * 
 * @array: array of commands and subcommands
 * 
 * Return: returns an array of strings of command followed by subcommands
 */
char **get_command(char **array, int *counter, char **pathArray, char *specificPath)
{
    char **command = NULL, *currentArg = NULL; /* BIN_DIR_PATH[256] = "/bin"; */
    int i = 0, j = 0, tokenSize = 10, comFlag = 0, stopDirFlag = 0;
    DIR *dir;

    command = malloc(tokenSize * sizeof(char*));
    if (command == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    while (array[i] && comFlag < 2)
    {
        /* If the first character is ‘/’, search only for the last part */
        if (array[i][0] == '/')
        {
            currentArg = slash_processor(array[i]);
        }
        else
            currentArg = strdup(array[i]);
        for (j = 0, stopDirFlag = 0; pathArray[j] != NULL && stopDirFlag == 0; j++)
        {
            printf("Trying PathArray[%d]: %s\n", j, pathArray[j]);
            dir = opendir(pathArray[j]);
            if (dir != NULL)
            {
                struct dirent *entry;
                printf("Going into this loop\n");
            /* printf("%d\n", comFlag); */
                while ((entry = readdir(dir)) != NULL)
                {
                    /* printf("%s\n", entry->d_name); */
                    if (strcmp(entry->d_name, currentArg) == 0)
                    {
                        specificPath = strdup(pathArray[j]);
                        printf("Specific Path: %s\n",specificPath);
                        comFlag ++;
                        stopDirFlag = 1;
                        break;
                    /* printf("Matching command found: %s\n", entry->d_name); */
                    }
                }
                closedir(dir);
            }
        }
        if (comFlag <= 1) /* Copy the command and arguments to the command array */
        {
            printf("Copying array[%d]: %s\n", i, currentArg);
            command[i] = strdup(currentArg);
            command[i + 1] = NULL; /* Set the last element to NULL */
            *counter += 1;
        }
        i++;
        free(currentArg);
    }
    return command;
}

/*
* tokenArraySub - subtract tokens from the front of tokenArray
*
* @array: temp storage for token
* 
* return: the stored token
*/

char **tokenArraySub(char **array, int *counter, int *flag)
{
    char **temp = NULL;
    int i = 0, j = 0;
    int tokenSize = 10;

    /* while (array[tokenSize] != NULL)
        tokenSize++;
    tokenSize = tokenSize - *counter + 1; */
    temp = malloc((tokenSize) * sizeof(char *));

    if (temp == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    i = *counter;
    /* printf("Flag: %d\n", *flag); */
    *flag -= *counter;
    /* printf("Flag: %d\n", *flag);
    printf("i = %d\n", i); */
    if (array[i] == NULL)
    {
        /* printf("this is to test if we get here"); */
        free(temp);
        return (array);
    }
    /* printf("Hello, lets check this\n"); */
    for (; array[i] != NULL; i++, j++)
    {
        temp[j] = strdup(array[i]);
        /* printf("%s: %s\n", temp[j], array[i]); */
        if (temp[j] == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }
    temp[j] = NULL;
    
    for (i = 0; array[i]; i++)
    {
        /*printf("testing pt two\n");
        printf("Freeing array[%d]", i); */
        free(array[i]);
    }
    free(array);

    *counter = 0;
    return (temp);    
}