#include <stdio.h>

int bubble_sort(int *list, int n)
{
    int i,j,temp;

    for(i=0; i < n-1 ;i++){
        for(j=0; j < n-1-i ;j++){
            if(list[j] > list[j+1]){
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}

int main()
{
        int list[10] = {9,3,6,14,4,30,2,17,15,21};

        for(int i=0; i<10;i++){
            printf("%2d ",list[i]);
        }

        bubble_sort(list,10);
        
        printf("\n");

        for(int i=0; i<10 ; i++){
            printf("%2d ",list[i]);
        }

        printf("\n");

        return 0;
}
