/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdint.h>
 #include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* file = fopen("card.raw","r");
    FILE* currOutFile=fopen("000.jpg","w");
    if (file == NULL)
    {
        printf("Could not open card.raw");
        return -1;
    }
    int counter=-1;
    uint8_t buffer[512];
    while(fread(buffer,sizeof(buffer),1,file)==1)
    {          
        if (buffer[0]==255 && buffer[1]==216 && buffer[2]==255 && (buffer[3]==224 || buffer[3]==225))
        {
            //Generate filename
            if(currOutFile!=NULL)
                fclose(currOutFile);
            counter++;
            char fileName[10];
            sprintf(fileName, "%.3d.jpg", counter);
            currOutFile=fopen(fileName,"w");
        }
            
        fwrite(buffer, sizeof(buffer), 1, currOutFile);        
    }
   
    
    free(file);
//    free(currOutFile);   
}
