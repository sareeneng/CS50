/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

void swap(int*, int*);
 
bool search(int value, int values[], int n)
{
    //Binary search
    //Base case - n=1 - if so, check number and return false if not number and return true if so
        
    if(n==1)
        if(values[0]==value)
            return true;
        else
            return false;
    else
    {
        int indexToCheck = n/2;
        
        if(values[indexToCheck]==value)
            return true;
        else if(values[indexToCheck]>value)
            return (false || search(value, &values[0], n/2));
        else
            return (false || search(value, &values[n/2+1], n/2-(n+1)%2));
    }
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // Guess I'll do bubble sort because it was easiest to remember
    // When arrays are passed in, it's the actual memory, not a copy
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-1-i; j++)
        {
            if(values[j+1]<values[j])
            {
/*                int temp = values[j+1];
                values[j+1]=values[j];
                values[j]=temp;*/
                swap(&values[j], &values[j+1]);
            }    
        }
    }
       
    return;
}


void swap(int* a, int* b)
{
    int temp = *a;
    *a=*b;
    *b=temp;
}

