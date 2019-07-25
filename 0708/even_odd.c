#include <stdio.h>

int even_odd(int a)
{
	if(a%2 == 0){
		printf("It is even\n");
	}
	else{
		printf("It is odd\n");
	}
}

int main()
{
	int data;
	while(1){

		printf("input : ");
		scanf("%d",&data);

		if(data == -99) break;

		even_odd(data);
	}
}
