#include <stdio.h>

int main()
{
	int i, result;
	
	for(i=0;i<100;i++){
		//result = i % 7;
		if((i%7) == 0){
			printf("%d\n",i);
		}
	}

	return 0;

}
