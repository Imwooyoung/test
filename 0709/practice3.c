#include <stdio.h>

int max_num(int *score)
{
    int max=0;
	for(int i=0;i<10;i++){
		if(*(score+i) > max){
			max = *(score+i);
		}
	}

    return max;
}

int main()
{
	int score[10] = {95,47,28,62,86,77,20,98,36,10};
	int max=0;

    max = max_num(score);

	printf("the biggist score : %d\n",max);

	return 0;
}	