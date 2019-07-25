#include <stdio.h>
#include <stdlib.h>

int main()
{
    int SizeofArray;
    int *p;

    printf("number of element : ");
    scanf("%d",&SizeofArray);

    p = (int*)malloc(SizeofArray * sizeof(int));

    for(int i=0; i< SizeofArray; i++){
        *(p+i) = i;
    }

    free(p);

    return 0;
}