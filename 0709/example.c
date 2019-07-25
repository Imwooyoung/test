#include <stdio.h>

int main()
{
    int data = 0x12345678,i;

    char *p1 = (char*) &data;
    int *p2 = &data;
    short *p3 = (short*) &data;

    printf("%x\n",&data);
    printf("%x\n",p1);
    printf("%x\n",p2);
    printf("%x\n",p3);


    for(i=0; i<8; i++){
        printf("%2x ",*(p1+i));
    }
    printf("\n");

    for(i=0; i<1; i++){
        printf("%2x ",*(p2+i));
    }
    printf("\n");

    for(i=0; i<2; i++){
        printf("%2x ",*(p3+i));
    }
    printf("\n");


    *p1 = 0x50;
    printf("%08x\n",data);

    return 0;
}
