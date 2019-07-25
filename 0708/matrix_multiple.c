#include <stdio.h>

int main()
{
	int array1[4][4] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	int array2[4][4] = {1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2};
	int result[4][4] = {0};

	int i,j,k;

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			for(k=0;k<4;k++){
				result[i][j] += array1[i][k] * array2[k][j];
			}
		}
	}

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			printf("%d ",result[i][j]);
		}
		printf("\n");
	}


	return 0;
}
