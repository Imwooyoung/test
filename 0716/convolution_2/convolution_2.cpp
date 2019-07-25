
#include <iostream>
#include <stdio.h>
#include <malloc.h>

void make_padding(int W,int C, int P, int** padding, int** p1)
{
    int i,j;

    for(i=0 ; i<P ; i++){
        for(j=0 ; j<(W+(2*P)) ; j++){
                padding[i][j] = 0;
        }   
    }

    for(i=P ; i< (W+P) ; i++){
        for(j=0 ; j<P ; j++){
            padding[i][j] = 0;
        }

        for(j=P ; j<C+P ; j++){
            padding[i][j] = p1[i-P][j-P];
        }

        for(j=C+P ; j<C+2*P ; j++){
            padding[i][j] = 0;
        }            
    }

    for(i=W+P ; i<W+2*P ; i++){
        for(j=W+P ; j<(C+(2*P)) ; j++){
                padding[i][j] = 0;
        }   
    }

    printf("padding :\n");
    for(i=0 ; i < W+(2*P) ;i++){
        for(j=0 ; j < C+(2*P) ; j++){
            printf("%d  ",padding[i][j]);
        }
        printf("\n\n");
    }        
}

void convolution(int Rw, int Rc, int F, int S, int** padding, int** p2, int** convolution)
{
    int i, j, k;
    int m, n, sum;
    printf("%d %d\n",Rw, Rc);
    for(m=0 ; m< Rw ; m=m+1){
        for(n=0 ; n < Rc ; n=n+1){
            sum = 0;
            for(i=0; i<F ; i++){
                for(j=0 ; j<F; j++){
                    sum = sum + (padding[S*m+i][S*n+j] * p2[i][j]);
                    //printf("%d ",sum);
                }
            }
            convolution[m][n] = sum;
        }
        
    }

    printf("convolution : \n");
    for(i=0 ; i < Rw ;i++){
        for(j=0 ; j<Rc ; j++){
            printf("%d  ",convolution[i][j]);
        }
        printf("\n\n");
    }        
}

int main()
{
    int i,j;
    int **p1,**p2, **padding, **conv, **pooling;

    int W,C,F,P,S;

    printf("W C N P S: ");
    scanf("%d %d %d %d %d",&W, &C, &F, &P, &S);

    int Rw = ((W-F+2*P)/S)+1;
    int Rc = ((C-F+2*P)/S)+1;

    //input
    p1 = (int**)malloc(W*sizeof(int*));

    for(i = 0; i < W ;i++){
        *(p1+i) = (int*)malloc(C*sizeof(int));
    }

    for(i=0 ; i < W ;i++){
        for(j=0 ; j < C ; j++){
            p1[i][j] = 1;
        }
    }

    //filter
    p2 = (int**)malloc(F*sizeof(int*));

    for(i = 0; i < F ;i++){
        *(p2+i) = (int*)malloc(F*sizeof(int));
    }

    for(i=0 ; i < F ;i++){
        for(j=0 ; j < F ; j++){
            p2[i][j] = 1;
        }
    }

    //padding
    padding = (int**)malloc((W+(2*P))*sizeof(int*));

    for(i = 0; i < (W+(2*P)) ;i++){
        *(padding+i) = (int*)malloc((C+(2*P))*sizeof(int));
    }

    //convolution
    conv = (int**)malloc(Rw*sizeof(int*));

    for(i = 0; i < Rw ;i++){
        *(conv+i) = (int*)malloc(Rc*sizeof(int));
    }

    make_padding(W,C,P,padding,p1);
    convolution(Rw,Rc,F,S,padding,p2,conv);


    for(i = 0; i < W ;i++){
        free(*(p1+i));
    }
        free(p1);

    for(i = 0; i < F ;i++){
        free(*(p2+i));
    }
    free(p2);

    for(i = 0; i < (W+(2*P)) ;i++){
        free(*(padding+i));
    }
        free(padding);

    for(i = 0; i < Rw ;i++){
        free(*(conv+i));
    }    




    //free(conv);

}