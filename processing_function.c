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
        tokenizer = strtok(NULL, "/");
    }
    tokenizedList[i] = NULL;

    for (i = 0; tokenizedList[i] != NULL; i++)
    {
        if (tokenizedList[i + 1] == NULL)
            finalCom = strdup(tokenizedList[i]);
        printf("%s\n", tokenizedList[i]);
        free(tokenizedList[i]);
    }
    printf("finalCom = %s\n", finalCom);
    free(tokenizedList);
    free(inputString);

    return (finalCom);
}


/**
 * get_command - returns commands and subcommands until second command appears
 * 
 * @array: array of commands and subcommands
 * 
 * Return: returns an array of strings of command followed by subcommands
 */
char **get_command(char **array, int *counter)
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
        if (comFlag <= 1) /* Copy the command and arguments to the command array */
        {
            printf("Copying array[%d]: %s\n", i, path);
            command[i] = strdup(path);
            command[i + 1] = NULL; /* Set the last element to NULL */
            *counter += 1;
        }
        i++;
        free(path);
    }
    return command;
}

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
    printf("Flag: %d\n", *flag);
    *flag -= *counter;
    printf("Flag: %d\n", *flag);
    printf("i = %d\n", i);
    if (array[i] == NULL)
    {
        printf("this is to test if we get here");
        free(temp);
        return (array);
    }
    printf("Hello, lets check this\n");
    for (; array[i] != NULL; i++, j++)
    {
        temp[j] = strdup(array[i]);
        printf("%s: %s", temp[j], array[i]);
        if (temp[j] == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }
    temp[j] = NULL;
    
    for (i = 0; array[i]; i++)
    {
        printf("testing pt two\n");
        printf("Freeing array[%d]", i);
        free(array[i]);
    }
    free(array);

    *counter = 0;
    return (temp);    
}