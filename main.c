#include "main.h"

/**
 * main - 
 * 
 * @argc - count of arguments given
 * 
 * @argv - array of arguments given
 * 
 * Return: 0 on success?
*/

int main(int argc, char **argv)
{
    int flag = 1; /*Flag for start/stop */

    while (flag)
    {
        printf("%s\n", PROMPT);
        buffer = get_input_mal();

        printf("%s", buffer);

        free(buffer);

        flag = 0;
    }
    return (0);
}
