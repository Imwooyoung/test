#include <stdio.h>

int main()
{
	int data;
	
	while(1){
		printf("input : ");
		scanf("%d",&data);
		if(data<100 && data>0) break;
		printf("not 0<data<100\n");
	}

	if(data > 50){
		printf("pass\n");
	} else{
		printf("fail\n");
	}

	return 0;
}
