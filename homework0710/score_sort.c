#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    char name[50];
    int score[5];
    double average, total;
};

int main()
{
    int i=0;
    FILE *fp;
    struct Student *p;
    char words[20];

    int n;

    fp = fopen("/home/socmgr/iuy/homework0710/students.txt","r");

    if(fp == NULL){
        printf("Read Error\n");
        return 0;
    }

    fscanf(fp,"student num : %d",&n);
    
    p = (struct student*)malloc(n * sizeof(struct Student));

    for(i=0; i<n ; i++){
        fscanf(fp," name: %s",p[i].name);

        fscanf(fp,"%s",&words);

        if(strcmp(words,"math:")==0){
            fscanf(fp,"%d",&p[i].score[0]);
        }
        else if(strcmp(words,"science:")==0){
            fscanf(fp,"%d",&p[i].score[1]);
        }
        else if(strcmp(words,"social:")==0){
            fscanf(fp,"%d",&p[i].score[2]);
        }


        fscanf(fp,"%s",&words);

        if(strcmp(words,"math:")==0){
            fscanf(fp,"%d",&p[i].score[0]);
        }
        else if(strcmp(words,"science:")==0){
            fscanf(fp,"%d",&p[i].score[1]);
        }
        else if(strcmp(words,"social:")==0){
            fscanf(fp,"%d",&p[i].score[2]);
        }


        fscanf(fp,"%s",&words);

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

        printf("name: %-10s  math:%3d, science:%3d, social:%3d average:%.2f \n", p[i].name, p[i].score[0], p[i].score[1], p[i].score[2], p[i].average);
    }

    printf("\n");

    fclose(fp);
    free(p);

    return 0;
}
