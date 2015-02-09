#include <stdio.h>

unsigned long hash(unsigned char*);

int main(void)
{
	long hashVal;
	unsigned char* test = "test";
	unsigned char* test2 = "testa";
	unsigned char* test3 = "test";
	
	hashVal = hash(test);
	printf("%lu\n%lu\n%lu\n",hash(test), hash(test2), hash(test3));
	
	return 0;
}

unsigned long hash(unsigned char* str)
    {
        if(str[1]!=NULL)
            return hash(&str[1])*33^str[0];
        else
            return 33^str[0];
    }

