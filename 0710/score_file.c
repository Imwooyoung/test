#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    char name[50];
    int score[5];
    double average, total;
};

/*
int main()
{
    int i;
    FILE *fp;
    struct Student *p;

    int n;

    printf("student num : ");
    scanf("%d",&n);

    p = (struct student*)malloc(n * sizeof(struct Student));

    fp = fopen("/home/socmgr/iuy/0710/students.txt","w");
    if(fp == NULL){
        printf("Write Error\n");
        return 0;
    }    

    for(i=0; i<n ; i++){
        printf("%d student name : ",i+1);
        scanf("%s",p[i].name);
        printf("math : ");
        scanf("%d",&p[i].score[0]);
        printf("science : ");
        scanf("%d",&p[i].score[1]);
        printf("social : ");
        scanf("%d",&p[i].score[2]);

        p[i].total = p[i].score[0] + p[i].score[1] + p[i].score[2];
        p[i].average = p[i].total / 3;
    }

    fprintf(fp,"student num : %d\n",n);
    for(i=0; i<n ; i++){
        fprintf(fp,"%s - math:%d, science:%d, social:%d average:%.2f \n",p[i].name,p[i].score[0],p[i].score[1],p[i].score[2],p[i].average);
    }

    fclose(fp);
    free(p);

    return 0;
}
*/

int main()
{
    int i=0;
    FILE *fp;
    struct Student *p;
    char words[20];

    int n;

    fp = fopen("/home/socmgr/iuy/0710/students.txt","r");

    if(fp == NULL){
        printf("Read Error\n");
        return 0;
    }

    fscanf(fp,"student num : %d",&n);
    
    p = (struct student*)malloc(n * sizeof(struct Student));

    for(i=0; i<n ; i++){
        fscanf(fp," name: %s",p[i].name);

        fscanf(fp," %s",&words);

        if(strcmp(words,"math:")==0){
            fscanf(fp,"%d",&p[i].score[0]);
        }
        else if(strcmp(words,"science:")==0){
            fscanf(fp,"%d",&p[i].score[1]);
        }
        else if(strcmp(words,"social:")==0){
            fscanf(fp,"%d",&p[i].score[2]);
        }


        fscanf(fp," %s",&words);

        if(strcmp(words,"math:")==0){
            fscanf(fp,"%d",&p[i].score[0]);
        }
        else if(strcmp(words,"science:")==0){
            fscanf(fp,"%d",&p[i].score[1]);
        }
        else if(strcmp(words,"social:")==0){
            fscanf(fp,"%d",&p[i].score[2]);
        }


        fscanf(fp," %s",&words);

        if(strcmp(words,"math:")==0){
            fscanf(fp,"%d",&p[i].score[0]);
        }
        else if(strcmp(words,"science:")==0){
            fscanf(fp,"%d",&p[i].score[1]);
        }
        else if(strcmp(words,"social:")==0){
            fscanf(fp,"%d",&p[i].score[2]);
        }

        fscanf(fp," average: %lf",&p[i].average);

        printf("name: %s  math:%d, science:%d, social:%d average:%.2f \n", p[i].name, p[i].score[0], p[i].score[1], p[i].score[2], p[i].average);
    }

    printf("\n");

    fclose(fp);
    free(p);

    return 0;
}
