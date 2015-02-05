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
    //Linear search
    for(int i=0; i<n; i++)
        if(values[i]==value)
            return true;
    
    return false;
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

