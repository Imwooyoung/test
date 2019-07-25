#include <stdio.h>

int main()
{
	int a;
	float b;
	char c;
	
	printf("int : ");
	scanf("%d",&a);

	printf("float : ");
	scanf("%f",&b);

	printf("char : ");
	scanf(" %c",&c);	
	
	printf("int = %6d\n",a);
	printf("float = %.2f\n",b);
	printf("char = %c\n",c);

	return 0;
}
