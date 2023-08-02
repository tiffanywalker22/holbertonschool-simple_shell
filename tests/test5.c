#include <stdio.h>
#include <string.h>

extern char **environ;
int main(int argc, char *argv[])
{
    int count = 0;

    printf("\n");
    while(environ[count] != NULL)
   {
         printf("[%s] :: ", environ[count]);
         count++;
   }

   return 0;
}

// extern char **environ;

// char *get_env_value(const char *var) {
//     for (int i = 0; environ[i] != NULL; i++) 
//     {
//         if (strcmp(environ[i], var)) 
//         {
//             return environ[i];
//         }
//     }
//     return NULL;
// }

// int main() {
//     char *path = get_env_value("PATH");
//     if (path != NULL) {
//         printf("PATH: %s\n", path);
//     } else {
//         printf("PATH environment variable not found.\n");
//     }

//     return 0;
// }
