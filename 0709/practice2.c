#include <stdio.h>

int main()
{
	int score[10] = {95,47,28,62,86,77,20,98,36,100};
	int *p;
	int i,order=0,max=0;

	p = score;

	for(i=0;i<10;i++){
		if(*(p+i) > max){
			max = *(p+i);
			order = i+1;
		}
	}

	printf("%d score is the biggist number %d\n",order,max);

	return 0;
}	
