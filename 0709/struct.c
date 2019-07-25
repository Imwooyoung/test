#include <stdio.h>

struct Student{
    char name[50];
    int score[5];
    double average, total;
    char pass_fail;
};

int main ()
{
    int i;
    struct Student student[2];

    for(i=0;i<2;i++){
        printf("%d student name : ",i+1);
        scanf("%s",student[i].name);
        printf("math : ");
        scanf("%d",&student[i].score[0]);
        printf("english : ");
        scanf("%d",&student[i].score[1]);
    }

    printf("\n");

    for(i = 0; i<2; i++){
        printf("%d Student name : %s\n",i+1,student[i].name);
        printf("%d Student math : %d\n",i+1,student[i].score[0]);
        printf("%d Student english : %d\n\n",i+1,student[i].score[1]);
    }
}
