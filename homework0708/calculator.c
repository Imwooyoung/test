#include <stdio.h>

int main()
{
	int mode,a,b;
	while(1){
		printf("input : ");
		scanf("%d %d",&a,&b);

		printf("What? 1.ADD 2.SUB 3.MUL 4.DIV 5.REM : (-99 end) ");
		scanf("%d",&mode);

		if(mode == -99) break;
		
		switch(mode){
			case 1 : printf("%d + %d = %d\n",a,b,a+b);
				 break;
			case 2 : printf("%d - %d = %d\n",a,b,a-b);
				 break;
			case 3 : printf("%d x %d = %d\n",a,b,a*b);
				 break;
			case 4 : printf("%d / %d = %.2f\n",a,b,a/(double)b);
				 break;
			case 5 : printf("%d %% %d = %d\n",a,b,a%b);
				 break;
			default : printf("Wrong number\n");
		}
	}
	return 0;
}
