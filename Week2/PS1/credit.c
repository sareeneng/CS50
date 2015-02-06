#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

string getCCType(long long);

int main (void)
{
    long long num;
    
    //Get credit card number to test. GetLongLong already has error checking and will reject non-integers. However, it would accept negative numbers (which we shouldn't allow)
    do
    {
        printf("Number: ");
        num = GetLongLong();
    }while(num<1);
    
    //verify that it is a valid number
    //1) Multiply every other digit by 2 starting with the SECOND-TO-LAST digit
    //2) Add the digits of the above (don't add the numbers together);
    //3) Add together the digits that weren't involved yet
    //4) if the total's last digit is 0, number is valid
    
    int sum=0;
    string ccType;
    
    while(num>0)
    {
        int currDig = num%10;
        sum += currDig;
        num = (num-currDig)/10;
            
        if(num > 9 && num < 99)
            ccType = getCCType(num);
        currDig = num%10;
        int addToSum;
        
        if(currDig*2 > 9) //if this is a double-digit number, we want to add the digits. This is equivalent to saying subtract 9 (e.g. if the number was 14, we want 5. if it was 16, we want 7)
            addToSum = currDig*2-9;
        else
            addToSum = currDig*2; 
            
        sum += addToSum;
        num = (num-currDig)/10;
        
        if(num > 9 && num < 99)
            ccType = getCCType(num);
    }
    
//    if(sum%10 == 0)
//        printf("VALID!\n");
//    else
//        printf("NOT VALID!\n");
    
    printf("%s\n",ccType);
    
}

string getCCType(long long n)
{
   // printf("test%llu",n);
    if(n>50 && n<56)
        return "MASTERCARD";
    else if (n==34 || n==37)
        return "AMEX";
    else if (n > 39 && n < 50)
        return "VISA";
        
    return "INVALID";

}
