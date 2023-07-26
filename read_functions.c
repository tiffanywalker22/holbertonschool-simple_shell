#include "main.h"

/**
 * get_input_mal - gets input from stdin
 * 
 * Return: Returns input from stdin
*/

char * get_input_mal(void)
{
    char *buffer;
    size_t buffSize = BUFF_SIZE;

    buffer = (char *)malloc(sizeof(char *) * buffSize);
    getline(&buffer, &buffSize, stdin);

    return (buffer);
}

/**
 * strtok - splits a string into tokens
 *
 * Return: pointer to first token found, or NULL
 */
 char * gettokens(char *buffer)
{
    
}