#include <stdio.h>

int main()
{
	int in,i=0,j=0;

	printf("input : ");
	scanf("%d",&in);

	i = in;
	while(i>0){
		while(j<i){
			printf("*");
			j++;
		}
		j=0;
		printf("\n");
		i--;
	}

/*
	for(i=in;i>0;i--){
		for(j=0;j<i+1;j++){
			printf("*");
		}
		printf("\n");
	}
*/
	return 0;
}
