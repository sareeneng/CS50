#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int h;
    
    do
    {
        printf("height: ");
        h = GetInt();
        if(h==0)
            return 0;
    }while(h<1 || h>23);

    int widthOfPyramid = h+1;

    for(int i=0; i<h; i++)
    {
        //for each line, print a right-aligned hash
        //first line should have two hashes
        //so number of hashes = i+2
        //e.g. in first line (i=0), two hashes
        //in last line(i=h-1), h-1+2 hashes = h+1 hashes
        
        char currString[i+3];
        currString[i+2]='\0'; // need to terminate each string
        
        for(int j=0; j<i+2; j++)
           currString[j]='#';
            
        printf("%*s\n", widthOfPyramid,currString);
        
    }

}
