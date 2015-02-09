//This pogram outputs initials. Only deals with spaces and letters

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    string name = GetString();
    char* pch = strtok(name," ,.-");
    while(pch != NULL)
    {
        printf("%c",toupper(pch[0]));
        pch = strtok(NULL," ,.-");
    }
    printf("\n");
    free(name);
    return 0;
}

