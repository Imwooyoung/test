#include <stdio.h>

int main()
{
	float kor, eng, math;
	float avg;

	while(1){
		printf("kor : ");
		scanf("%f", &kor);
		printf("eng : ");
		scanf("%f", &eng);
		printf("math : ");
		scanf("%f", &math);

		avg = (kor+eng+math)/3.0;

		printf("avg = %f\n",avg);
	
		if(avg>90){
			printf("scholarship\n");
		}
		else if(avg > 50){
			printf("good job\n");
		}
		else{
			printf("your fail\n");
		}

		if(kor>95 && eng> 95 && math > 95){
			printf("you are special scholarship\n");
		}
	}

	return 0;
}
