#include <stdio.h>

int main()
{
/*	int a[4] = {1,2,3,4};
	int *p = a;
	int sum = 0;

	while(p-a <=3){
		sum += *p;
		p++;
	}
	printf("sum: %d\n",sum);

	


	int student[11] = {90,84,34,97,54,67,72,30,16,75,91};

	printf("student[]'s address %x\n",&student[0]);
	printf("student's value %x\n",&student);


*/
	int student[11] = {90,84,34,97,54,67,72,30,16,75,91};

	for(int i=0;i<11;i++){
		printf("student[%d]'s address %x\n",i,&student[i]);
	}


/*
	int *p, **pp;
	int a = 3;

	p = &a;
	pp = &p;

	printf("%x\n",&*p);
	printf("%x\n",*&p);
	printf("%x\n",**pp);
*/
	return 0;
}
