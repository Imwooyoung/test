#include <stdio.h>

int change_box(int *p)
{
        printf("chage boc function start\n");
        printf("p value in function: %x, value pointed by p: %d\n",p,*p);
        *p = 10;
        printf("change_box end\n\n");
        return 0;
}

int main()
{
    int i=0;
    printf("i address : %x\n",&i);
    printf("i value before call : %d\n\n",i);
    change_box(&i);
    printf("i value after call : %d\n\n",i);
    return 0;
}