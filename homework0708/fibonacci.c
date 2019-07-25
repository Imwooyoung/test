#include <stdio.h>

void fibonacci(int step)
{
	int i;
	int a=0,b=1,c=1;

	for(i=0;i<step;i++){
		
		printf("%d\n",c);
		a = b;
		b = c;
		c = a+b;
	}
}
		

int main()
{
	int step;

	printf("How Long? : ");
	scanf("%d",&step);
	
	fibonacci(step);

	return 0;
}
