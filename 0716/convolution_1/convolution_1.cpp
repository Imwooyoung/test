
#include <iostream>
#include <stdio.h>
#include <malloc.h>

int main()
{
    int i,j,k;
    int **p1,**p2,**padding, **convol, **pooling, **convolution;
    int W,F,P,S;

    printf("W N P S: ");
    scanf("%d %d %d %d",&W, &F, &P, &S);

    //input
    p1 = (int**)malloc(W*sizeof(int*));

    for(i = 0; i < W ;i++){
        *(p1+i) = (int*)malloc(W*sizeof(int));
    }

    for(i=0 ; i < W ;i++){
        for(j=0 ; j < W ; j++){
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
        *(padding+i) = (int*)malloc((W+(2*P))*sizeof(int));
    }


    for(i=0 ; i<P ; i++){
        for(j=0 ; j<(W+(2*P)) ; j++){
                padding[i][j] = 0;
        }   
    }

    for(i=P ; i< (W+P) ; i++){
        for(j=0 ; j<P ; j++){
            padding[i][j] = 0;
        }

        for(j=P ; j<W+P ; j++){
            padding[i][j] = p1[i-P][j-P];
        }

        for(j=W+P ; j<W+2*P ; j++){
            padding[i][j] = 0;
        }            
    }

    for(i=W+P ; i<W+2*P ; i++){
        for(j=W+P ; j<(W+(2*P)) ; j++){
                padding[i][j] = 0;
        }   
    }    


    printf("filter :\n");
    for(i=0 ; i < F ;i++){
        for(j=0 ; j<F ; j++){
            printf("%d  ",p2[i][j]);
        }
        printf("\n\n");
    }

    printf("padding :\n");
    for(i=0 ; i < W+(2*P) ;i++){
        for(j=0 ; j < W+(2*P) ; j++){
            printf("%d  ",padding[i][j]);
        }
        printf("\n\n");
    }    

    //pooling
    convol = (int**)malloc(F*sizeof(int*));

    for(i = 0; i < F ;i++){
        *(convol+i) = (int*)malloc(F*sizeof(int));
    }

    int R = ((W-F+2*P)/S)+1;
    pooling = (int**)malloc(R*sizeof(int*));

    for(i = 0; i < R ;i++){
        *(pooling+i) = (int*)malloc(R*sizeof(int));
    }        

    int m=0,n=0,max;
    for(k=0 ; k< R*R; k++){
        m = S*(k/R);
        n = S*(k%R);
        max = 0;
        for(i=0; i<F ; i++){
            for(j=0 ; j<F; j++){
                convol[i][j] = padding[m+i][n+j] * p2[i][j];
                if(max < convol[i][j]){
                    max = convol[i][j];
                }
            }
        }
        m = (k/R);
        n = (k%R);
        pooling[m][n] = max;
    }

    printf("pooling :\n");
    for(i=0 ; i < R ;i++){
        for(j=0 ; j<R ; j++){
            printf("%d  ",pooling[i][j]);
        }
        printf("\n\n");
    }        

    convolution = (int**)malloc(R*sizeof(int*));

    for(i = 0; i < R ;i++){
        *(convolution+i) = (int*)malloc(R*sizeof(int));
    }   

    int sum;
    for(k=0 ; k< R*R; k++){
        m = S*(k/R);
        n = S*(k%R);
        sum = 0;
        for(i=0; i<F ; i++){
            for(j=0 ; j<F; j++){
                sum = sum + (padding[m+i][n+j] * p2[i][j]);
            }
        }
        m = (k/R);
        n = (k%R);
        convolution[m][n] = sum;
    }

    printf("convolution : \n");
    for(i=0 ; i < R ;i++){
        for(j=0 ; j<R ; j++){
            printf("%d  ",convolution[i][j]);
        }
        printf("\n\n");
    }     

    for(i = 0; i < W ;i++){
        free(*(p1+i));
    }

    for(i = 0; i < F ;i++){
        free(*(p2+i));
        free(*(convol+i));
    }

    for(i = 0; i < (W+(2*P)) ;i++){
        free(*(padding+i));
    }

    for(i = 0; i < R ;i++){
        free(*(pooling+i));
        free(*(convolution+i));
    }    
    
    free(p1);
    free(p2);
    free(padding);
    free(convol);
    free(pooling);
    free(convolution);
    
}