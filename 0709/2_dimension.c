#include <stdio.h>

int main()
{
	int a[2][3] = {{1,2,3},{4,5,6}};
	printf("a: %x\n",a);
	printf("&a[0]: %x\n",&a[0]);
	
	printf("a[0]: %x\n",a[0]);
	printf("&a[0][0]: %x\n",a[0][0]);
	printf("a[1]: %x\n",a[1]);
	printf("&a[1][0]: %x\n",a[1][0]);

	return 0;
}

/*
int main()
{
	int a[2][3] = {{1,2,3},{4,5,6}};

	printf("&a[0][0]: %x\n",&a[0][0]);
	printf("&a[0][1]: %x\n",&a[0][1]);
	printf("a[0]+1: %x\n",a[0]+1);

	return 0;
}


int main()
{
	int a[2][3] = {{1,2,3},{4,5,6}};
	
	printf("a: %x,a+1: %x\n",a[0], a[1]);
	
	return 0;
}*/
