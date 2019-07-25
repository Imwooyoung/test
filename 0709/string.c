#include <stdio.h>

int main()
{
    char word_1[4] = {'K','I','M','\0'};
    char word_2[4] = {'K','I','M',0};
    char word_3[4] = {'K','I','M',NULL};
    char word_4[4] = {"KIM"};    

    printf("word_1 : %s \n", word_1);
    printf("word_2 : %s \n", word_2);
    printf("word_3 : %s \n", word_3);
    printf("word_4 : %s \n", word_4);

    return 0;
}