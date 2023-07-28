#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char BIN_DIR_PATH[256] = "/bin"; /*Default bin directory path */

void set_bin_directory(const char *path) 
{
    strncpy(BIN_DIR_PATH, path, sizeof(BIN_DIR_PATH) - 1);
}

int search_bin_directory(const char *command) 
{
    DIR *dir;
    struct dirent *ent;

    dir = opendir(BIN_DIR_PATH);
    if (dir == NULL) {
        perror("Error opening directory");
        return -1;
    }

    while ((ent = readdir(dir)) != NULL) 
    {
        if (strcmp(ent->d_name, command) == 0) 
        {
            printf("Command '%s' found in %s\n", command, BIN_DIR_PATH);
            closedir(dir);
            return 1;
        }
    }

    closedir(dir);
    printf("Command '%s' not found in %s\n", command, BIN_DIR_PATH);
    return 0;
}

int main() 
{
    char command[100];
    char new_path[256];

    printf("Enter the command you want to search for: ");
    scanf("%s", command);

    printf("Current bin directory path: %s\n", BIN_DIR_PATH);
    printf("Do you want to change the bin directory path? (y/n): ");
    char response[10];
    scanf("%s", response);

    if (response[0] == 'y' || response[0] == 'Y') 
    {
        printf("Enter the new bin directory path: ");
        scanf("%s", new_path);
        set_bin_directory(new_path);
        printf("Bin directory path changed to: %s\n", BIN_DIR_PATH);
    }

    search_bin_directory(command);

    return 0;
}