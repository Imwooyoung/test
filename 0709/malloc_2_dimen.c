#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m,n;
    int i;
    char **p;

    printf("input m,n : ");
    scanf("%d %d",&m,&n);

    p = (char**)malloc(m*sizeof(char*));

    for(i=0;i<m;i++){
        *(p+i) = (char*)malloc(n * sizeof(char));
    }

    for(i=0;i<m;i++){
        for(int j=0;j<n;j++){
            p[i][j] = 0;
            printf("%d ",p[i][j]);
        }
        printf("\n");
    }

    for(i=0;i<m;i++){
        free(*(p+i));
    }
    free(p);

    return 0;
}