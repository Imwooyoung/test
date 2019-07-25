#include <stdio.h>

int main()
{
	int *p,a,b;
/*
	p = &a;
	*p = 2;
	p = &b;
	*p = 4;

	printf("a : %d\n",a);
	printf("b : %d\n",b);

	int *p;
	int a;
*/
	p = &a;
	a = 10;

	printf("The value of p : %x\n",p);
	printf("Place where a is saved : %x\n",&a);
	printf("%x\n",*p);

	return 0;
}
