#include <stdio.h>

int change_num(int *a, int *b)
{
    
    printf("before function a: %d, b: %d\n\n",*a,*b);
    *a = 10;
    *b = 10;
    printf("After function a: %d, b: %d\n\n",*a,*b);
    return 0;
}

int main()
{
    int a=5,b=7;

    change_num(&a, &b);

    return 0;
}