#include <stdio.h>

/* 
int main()
{
    char word[50];
    printf("no Space input \n: ");
    scanf("%s",word);

    printf("input string : %s\n",word);
}
*/

int main()
{
    char word[50];
    printf("input \n: ");
    scanf("%[^\n]",word);

    printf("input string : %s\n",word);

    return 0;
}