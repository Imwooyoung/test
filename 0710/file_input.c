#include <stdio.h>
/* 
int main()
{
    FILE *fp;
    fp = fopen("/home/socmgr/iuy/0710/test.txt","w");
    if(fp == NULL){
        printf("Write Error\n");
        return 0;
    }

    //fprintf(fp, "Hello World!\n");
    fputs("Hello World!!!",fp);
    fclose(fp);

    return 0;
}


int main()
{
    FILE *fp;
    fp = fopen("/home/socmgr/iuy/0710/test.txt","r");
    char words;

    while((words = fgetc(fp))!=EOF){
        printf("%c",words);
    }

    fclose(fp);

    return 0;
}


int main()
{
    FILE *fp;
    fp = fopen("/home/socmgr/iuy/0710/test.txt","r");
    char words[20];
    if(fp == NULL){
        printf("Read Error\n");
        return 0;
    }
    
    //fscanf(fp,"%s",words);
    fgets(words,20,fp);
    printf("contents : %s\n",words);

    fclose(fp);

    return 0;
}

*/
int main()
{
    FILE *fp;
    fp = fopen("/home/socmgr/iuy/0710/test.txt","r");
    char words[20];
    if(fp == NULL){
        printf("Read Error\n");
        return 0;
    }
    
    while(fscanf(fp,"%s",words) != EOF){
        printf("%s",words);
    }

    fclose(fp);

    return 0;
}
