#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

void dictionaryAttack(string, string);

int main(int argc, string argv[])
{
     if(argc!=2)
    {
        printf("Only one argument accepted\n");
        return -1;
    }
    
    string fullKey = argv[1];
    
    //Get salt, which is the first two letters of the encrypted key passed into the program
    char salt[3];
    salt[0]=fullKey[0];
    salt[1]=fullKey[1];
    salt[2]='\0';   //terminate string
    
    //Extract the key without the salt in it into a new string
    char keyWithoutSalt[strlen(fullKey)-2];                     
    strncpy(keyWithoutSalt, &fullKey[2],strlen(fullKey)-1);     //copies everything but 1st two chars
    keyWithoutSalt[strlen(keyWithoutSalt)]='\0';                //Terminate string
    
   
   
    //So now I have the salt and the key without the salt in two separate variables
    //Next, let's try a dictionary attack first
    
    dictionaryAttack(salt,fullKey);
        
    return 0;
}

void dictionaryAttack(string salt, const string fullKey)
{
    //Runs a dictionary attack on the salt to see if we can come up with the same key
    //Dictionary located at /usr/share/dict/words
    FILE *ifp;
    char *mode = "r";
    ifp=fopen("/usr/share/dict/words",mode);
    //ifp=fopen("testDict",mode);
    
    char buff[1024];
    
    while(fgets(buff,1024,ifp) != NULL)
    {   
        char* unencDict=buff;
        unencDict[strlen(unencDict)-1]='\0';
        string encDict = crypt(unencDict,salt);
        if(strcmp(fullKey,encDict)==0)
        {
            printf("%s\n",unencDict);
            fclose(ifp);
        }
    }
    
}
