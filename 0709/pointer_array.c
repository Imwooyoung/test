#include <stdio.h>

int main()
{
    int a[2][3] = {{1,2,3},{4,5,6}};

    printf("a bite : %d\n", sizeof(a));
    printf("a size : %d\n", sizeof(a)/sizeof(int));

    return 0;
}
