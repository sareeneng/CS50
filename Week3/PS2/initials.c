//This pogram outputs initials. Only deals with spaces and letters

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    for(int i=1; i<argc; i++)
        printf("%c",toupper(argv[i][0]));
    
    printf("\n");
}

