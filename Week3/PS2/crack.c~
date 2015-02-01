#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

bool dictionaryAttack(string, string);
char *GetSalt(string);
char *GetKeyWithoutSalt(string);
void bruteForce(string, int, int, string, string);

bool found = false;

int main(int argc, string argv[])
{   
    if(argc!=2)
    {
        printf("Only one argument accepted\n");
        return -1;
    }
    
    string fullKey = argv[1];
    
    string salt = GetSalt(fullKey);//Get salt, which is the first two letters of the encrypted key passed into the program
    
    if(dictionaryAttack(salt,fullKey)) //First let's run a dictionary attack and see if we get lucky
        return 0;                       //If successful, end program. Otherwise, move on.
    
    
    //Extract the key without the salt in it into a new string
    char *keyWithoutSalt = malloc(strlen(fullKey-2));
    keyWithoutSalt = GetKeyWithoutSalt(fullKey);                     
   
    //So now I have the salt and the key without the salt in two separate variables
    //And I know that my word is not in the dictionary
    //So now I need to brute-force it. 
    
    string prefix=malloc(4);
    bruteForce(prefix,0,8, salt, fullKey);
        
    return 0;
}

bool dictionaryAttack(string salt, const string fullKey)
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
            return true;
        }
    }
    
    return false;
    
}

char *GetSalt(string fullKey)
{
    char *salt = malloc(3);
    salt[0]=fullKey[0];
    salt[1]=fullKey[1];
    salt[2]='\0';   //terminate string
    
    return salt;   
}

char *GetKeyWithoutSalt(string fullKey)
{
    char *keyWithoutSalt = malloc(strlen(fullKey)-1);
    strncpy(keyWithoutSalt, &fullKey[2],strlen(fullKey)-1);     //copies everything but 1st two chars
    keyWithoutSalt[strlen(keyWithoutSalt)]='\0';                //Terminate string

    return keyWithoutSalt;
}

void bruteForce(string prefix, int currPosition, int maxLen, string salt, string fullKey)
{   
    //Function should terminate if we are higher than maxLen
    if (currPosition!=maxLen && !found)
    {
        //Make a copy of our current prefix in a different part of memory
        string prefixCopy = malloc(strlen(prefix)+1);
        strcpy(prefixCopy, prefix);
        
        //Now we can do operations on prefix
        
        for(int i=0; i<=126; i++)
        {
            prefix[currPosition]=i;
            if(strlen(prefix)>0)
            {
                string encCurrString = crypt(prefix,salt);
                if(strcmp(encCurrString,fullKey)==0)
                {
                    printf("%s\n",prefix);
                    found=true;
                }
            }
            if(i==0)
                i=32;   //Skip all the non-printable characters
            if(!found)
                bruteForce(prefix, currPosition+1, maxLen, salt, fullKey);
        }
    }

}
