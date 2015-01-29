#include <stdio.h>

int cube(int a);

int main(void)
{
    int x=2;
    printf("x is now %i\n", x);
    x = cube(x);
    printf("x cubed is %i\n", x);
}

int cube(int x)
{
    return x*x*x;
}
