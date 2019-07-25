#include <stdio.h>

struct Test{
    int a,b,c,d;
};

int main()
{
    struct Test test_st;
    struct Test *p_st;

    printf("%d\n",sizeof(test_st));
    printf("%d\n",sizeof(p_st));

    p_st = &test_st;

    (*p_st).a = 1;
    (*p_st).b = 2;

    printf("test_st a : %d\n", test_st.a);
    printf("test_st b : %d\n", test_st.b);

    return 0;
}
/*

struct Test{
    int a, b;
};

int init_struct(struct Test *st,int a, int b){
    st ->a = a;
    st ->b = b;

    return 0;
}

int main()
{
    struct Test st1;

    init_struct(&st1,1,2);
    printf("st1 a: %d, b: %d\n",st1.a,st1.b);

    return 0;
}*/
