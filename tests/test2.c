#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>


int main(int argc, char* argv)
{
  char* l = NULL;
  size_t n;
  while (getline(&l,&n, stdin) != -1 )
    {
      printf("%s\n",l);
      printf("%s\n", argv);
    }
  free(l); // don't forget to release the allocated memory
           // mmh, yes, here it's not useful since the program
           // ends.
}