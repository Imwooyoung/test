#include <stdio.h>

int main()
{
	int i;
	int score[5]={0};
	float sum=0;

	for(i=0;i<5;i++){
		printf("%d score : ",i+1);
		scanf("%d",&score[i]);
	}
	
	for(i=0;i<5;i++){
		sum = sum + score[i];
	}

	printf("\n");

	for(i=0;i<5;i++){
		if(score[i] > 60){
			printf("%d student %d : pass\n",i+1,score[i]);
		}
		else{
			printf("%d student %d : fail\n",i+1,score[i]);
		}
	}
	
	printf("average : %.2f\n", sum/5.0);
	return 0;
}

