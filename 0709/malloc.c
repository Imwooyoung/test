#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num = 0;
    int *p1, *p2;

    p1 = &num;

    printf("p2 address : %x\n",p2);

    p2 = (int*)malloc(sizeof(int));

    printf("p1 address : %x\n",p1);
    printf("p2 address : %x\n",p2);

    free(p2);

    return 0;
}