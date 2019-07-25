#include <stdio.h>

int main()
{
    char word[50]={0};
    int cnt=0;

    printf("input string: ");
    scanf("%s",word);

    for(int i=0;i<50;i++){
        if(word[i] != NULL){
            cnt++;
        }
    }
    
    printf("the number of string : %d\n",cnt);

    return 0;
}
