#include <stdio.h>

void max_prime(int data)
{
	int i,j, max=0;
	
	for(i=1;i<data;i++){
		for(j=2;j<i;j++){
			if(i % j == 0){
				break;
			}
		}
		if(i==j){
			max = j;
		}
	}
	printf("Maximum Prime Number : %d\n",max);
}
			

int main()
{
	int data;

	printf("input : ");
	scanf("%d",&data);

	max_prime(data);

	return 0;
}

	

