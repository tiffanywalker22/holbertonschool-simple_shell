/**
 * get_command - gets the first input for a command
 * 
 * @array: array of strings inputted
 * 
 * Return: returns a single character pointer
 */
char **get_command(char **array)
{
    char **command = NULL;
    char BIN_DIR_PATH[256] = "/bin";
    int i = 0, j;
    char *path;
    DIR *dir;
    while (array[i] != NULL)
    {
        /* If the first character is ‘/’, search only for the last part */
        if (array[i][0] == '/')
        {
            path = strdup(array[i] + 1); /* Skip the leading ‘/’*/
        }
        else
        {
            path = strdup(array[i]);
        }
        dir = opendir(BIN_DIR_PATH);
        if (dir != NULL)
        {
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL)
            {
                if (strcmp(entry->d_name, path) == 0)
                {
                    /* Found the command in the default path, create the command array */
                    command = malloc((i + 2) * sizeof(char *));
                    if (command == NULL)
                    {
                        perror("malloc");
                        exit(EXIT_FAILURE);
                    }
                    /* Copy the command and arguments to the command array */
                    for (j = 0; j <= i; j++)
                    {
                        command[j] = strdup(array[j]);
                    }
                    command[i + 1] = NULL; /* Set the last element to NULL */
                    /* Free memory and close the directory */
                    free(path);
                    closedir(dir);
                    return command;
                }
            }
            closedir(dir);
        }
        free(path);
        i++;
    }
    return command;
}
