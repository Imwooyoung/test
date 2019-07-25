#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m,n,m2,n2;
    int i,j,k;
    int **p1,**p2,**p3;

//input matrix1
    printf("matrix1 m,n : ");
    scanf("%d %d",&m,&n);

    p1 = (int**)malloc(m*sizeof(int*));

    for(i = 0; i < m ;i++){
        *(p1+i) = (int*)malloc(n * sizeof(int));
    }

    printf("first matrix : \n");
    for(i=0 ; i < m ;i++){
        for(j=0;j<n;j++){
            printf("p[%d][%d] : ",i,j);
            scanf("%d",&p1[i][j]);
        }
    }
    printf("\nmatrix1 :\n");
    for(i=0 ; i < m ;i++){
        for(j=0;j<n;j++){
            printf("%d ",p1[i][j]);
        }
        printf("\n");
    }

//input matrix 2
    while(n != m2){
        printf("\nmatrix2 m,n : ");
        scanf("%d %d",&m2,&n2);
        if(n != m2) printf("wrong size!!!\n");
    }


    p2 = (int**)malloc(m2*sizeof(int*));

    for(i = 0; i < m ;i++){
        *(p2+i) = (int*)malloc(n2 * sizeof(int));
    }

    printf("\nsecond matrix : \n");
    for(i=0 ; i < m2 ;i++){
        for(j=0;j<n2;j++){
            printf("p[%d][%d] : ",i,j);
            scanf("%d",&p2[i][j]);
        }
    }
    printf("\nmatrix2 : \n");
    for(i=0 ; i < m2 ;i++){
        for(j=0;j<n2;j++){
            printf("%d ",p2[i][j]);
        }
        printf("\n");
    }

//multiplication
    p3 = (int**)malloc(m*sizeof(int*));

    for(i = 0; i < m ;i++){
        *(p3+i) = (int*)malloc(n2 * sizeof(int));
    }

    for(i=0;i<m;i++){
        for(j=0; j < n2; j++){
            p3[i][j] = 0;
        }
    }

	for(i=0; i < m; i++){
		for(j=0; j < n2; j++){
			for(k=0; k < n; k++){
				p3[i][j] += (p1[i][k] * p2[k][j]);
			}
		}
	}

    printf("\nresult :\n");
	for(i=0; i<m; i++){
		for(j=0; j<n2; j++){
			printf("%d ",p3[i][j]);
		}
		printf("\n");
	}

	free(p1);
	free(p2);
	free(p3);
	return 0;
}
