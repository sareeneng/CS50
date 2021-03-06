/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Makes sure that the number of numbers to generate was passed in. Optionally the user can also give a seed. If the number of arguments is <1 or >2 then fail.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Converts the number to generate string to an  integer
    int n = atoi(argv[1]);

    // If a seed was passed, then use it, otherwise don't and use the current time as the seed. srand48 is an initializer function
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // drand48 is the actual random # generator. It gives float numbers between 0-1 to double-precision, and then multiplies by our limit to give the random number of desire (casted to an int to round).
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
