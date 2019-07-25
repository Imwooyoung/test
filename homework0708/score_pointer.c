#include <stdio.h>

int main()
{
	int i;
	int score[5] = {0};
	int *p = score;
	int sum = 0;

	for(i=0;i<5;i++){
		printf("Student %d score : ",i+1);
		scanf("%d", score+i);
	}

	printf("\n");

	for(i=0;i<5;i++){
		if(*(score+i) >60){
			printf("Student %d score : %d , Pass\n", i+1, *(score+i));
		}
		else{
			printf("Student %d score : %d , Fail\n", i+1, *(score+i));
		}
	}

	while(p-score <= 4){
		sum += *p;
		p++;
	}

	printf("average : %.2f\n",sum/5.0);

	return 0;
}

	
