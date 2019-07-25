#include <stdio.h>

int call_add(int a, int b)
{
	int sum = a+b;
	return sum;
}

int main()
{
	int c,d;
	scanf("%d %d",&c, &d);
	int sum = call_add(c,d);
	printf("%d + %d = %d\n",c,d,sum);
	return 0;
}
