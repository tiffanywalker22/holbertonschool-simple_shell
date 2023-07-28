#include "main.h"

/**
 * sigintCall - Calls the end of the function with control d or c
 * 
 * signal - Signals the call for end of function.
 */

void sigintCall(int signal)
{
    printf("\nReceived Ctrl+D. Exiting the program.\n");

    /* Call Frees if need to */

    exit(0);
}