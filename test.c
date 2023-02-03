#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int ac, char **av)
{
    printf("%s\n", getcwd(NULL, 0));
    chdir(getenv("HOME"));
    printf("%s\n", getcwd(NULL, 0));
}