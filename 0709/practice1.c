#include <stdio.h>

int main()
{
	int a[10] = {0,};
	int *p;
	int i,j;

	p = a;

	for(i=0;i<10;i++){
		for(j=1;j<i+2;j++){
			*(p+i) += j;
		}
		printf("%d ",*(p+i));
	}
	printf("\n");	

	return 0;
}
