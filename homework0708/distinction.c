#include <stdio.h>

void even_odd(int data)
{
	if(data%2 == 0){
		printf("It is EVEN\n");
	}
	else{
		printf("It is ODD\n");
	}
}

void prime_num(int data)
{
	int i, flag = 0;
	
	for(i=2;i<data;i++){
		if(data % i == 0){
			flag = 1;
			break;
		}
		else{
			flag = 0;
		}
	}
	
	if(flag == 0) printf("It is Prime Number!\n");
	else printf("It is NOT! prime number\n");
}

void square(int data)
{
	int i, flag=0;

	for(i=2;i<data;i++){
		if(i*i == data){
			flag = 1;
			break;
		}
		else{
			flag = 0;
		}
	}

	if(flag == 1){
		printf("It is Square Number\n");
	}
	else{
		printf("It is NOT! square number\n");
	}

}

int main()
{
	int data;
	
	printf("input : ");
	scanf("%d",&data);

	even_odd(data);
	prime_num(data);
	square(data);	

	return 0;
}

	
