#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace cv;
using namespace std;


void make_padding(int W, int P, int** input, int** padding)
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

        for(j=P ; j<W+P ; j++){
            padding[i][j] = input[i-P][j-P];
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
}

void Convolution(int R, int F, int S, int** padding, int filter[][5], int** conv)
{
    int i, j, k;
    int m, n, sum;
    for(k=0 ; k< R*R; k++){
        m = S*(k/R);
        n = S*(k%R);
        sum = 0;
        for(i=0; i<F ; i++){
            for(j=0 ; j<F; j++){
                sum = sum + (padding[m+i][n+j] * filter[i][j]);
            }
        }
        m = (k/R);
        n = (k%R);
        conv[m][n] = sum;
    }
}

int main()
{
    Mat image;
    image = imread("test.jpg",IMREAD_COLOR);
    if(image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    namedWindow("Original",WINDOW_AUTOSIZE);
    imshow("Original",image);

    int **aR, **aG, **aB;
    int **pad_R, **pad_G, **pad_B;
    int **conv_R, **conv_G, **conv_B;
    int W,F,P,S;
    int i,j;

    W = image.rows;

    //R,G,B 2_dimensional array
    aR = (int**)malloc(W*sizeof(int*));
    for(i = 0; i < W ;i++){
        *(aR+i) = (int*)malloc(W*sizeof(int));
    }

    aG = (int**)malloc(W*sizeof(int*));
    for(i = 0; i < W ;i++){
        *(aG+i) = (int*)malloc(W*sizeof(int));
    }

    aB = (int**)malloc(W*sizeof(int*));
    for(i = 0; i < W ;i++){
        *(aB+i) = (int*)malloc(W*sizeof(int));
    } 

    int x,y;
    for(y=0; y<W ; y++)
    {
        for(x=0 ; x<W ; x++)
        {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y,x);
            aR[y][x] = image.at<cv::Vec3b>(y,x)[2];  //R
            aG[y][x] = image.at<cv::Vec3b>(y,x)[1];  //G
            aB[y][x] = image.at<cv::Vec3b>(y,x)[0];  //B
        }
    }  
    
    printf("Padding rate : ");
    scanf("%d",&P);

    printf("Stride value : ");
    scanf("%d",&S);    

    // padding memory allocation
    pad_R = (int**)malloc((W+(2*P))*sizeof(int*));
    for(i = 0; i < (W+(2*P)) ;i++){
        *(pad_R+i) = (int*)malloc((W+(2*P))*sizeof(int));
    }

    pad_G = (int**)malloc((W+(2*P))*sizeof(int*));
    for(i = 0; i < (W+(2*P)) ;i++){
        *(pad_G+i) = (int*)malloc((W+(2*P))*sizeof(int));
    }    

    pad_B = (int**)malloc((W+(2*P))*sizeof(int*));
    for(i = 0; i < (W+(2*P)) ;i++){
        *(pad_B+i) = (int*)malloc((W+(2*P))*sizeof(int));
    }    

    make_padding(W, P, aR, pad_R);
    make_padding(W, P, aG, pad_G);
    make_padding(W, P, aB, pad_B);

    Mat image_pad(image.rows+2*P,image.cols+2*P,CV_8UC3);

    for(y=0; y<image_pad.rows ; y++)
    {
        for(x=0 ; x<image_pad.cols ; x++)
        {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y,x);
            image_pad.at<cv::Vec3b>(y,x)[2] = pad_R[y][x];
            image_pad.at<cv::Vec3b>(y,x)[1] = pad_G[y][x];
            image_pad.at<cv::Vec3b>(y,x)[0] = pad_B[y][x];
        }
    }    

    //imwrite("test1.jpg",image_pad);

    //namedWindow("padding",WINDOW_AUTOSIZE);
    //imshow("padding",image_pad);

/*
    //edge detect
    int Edge[3][3] = {{-1, -1, -1},{-1, 8, -1},{-1, -1, -1}};
    int R = ((W-3+2*P)/S)+1;

    conv_R = (int**)malloc(R*sizeof(int*));
    for(i = 0; i < R ;i++){
        *(conv_R+i) = (int*)malloc(R*sizeof(int));
    }

    conv_G = (int**)malloc(R*sizeof(int*));
    for(i = 0; i < R ;i++){
        *(conv_G+i) = (int*)malloc(R*sizeof(int));
    }

    conv_B = (int**)malloc(R*sizeof(int*));
    for(i = 0; i < R ;i++){
        *(conv_B+i) = (int*)malloc(R*sizeof(int));
    }

    Convolution(R,3,S,pad_R,Edge,conv_R);
    Convolution(R,3,S,pad_G,Edge,conv_G);
    Convolution(R,3,S,pad_B,Edge,conv_B);      
*/
/*
    int Blur[3][3] = {{1, 2, 1},{2, 4, 2},{1, 2, 1}};
    int R = ((W-3+2*P)/S)+1;

    conv_R = (int**)malloc(R*sizeof(int*));
    for(i = 0; i < R ;i++){
        *(conv_R+i) = (int*)malloc(R*sizeof(int));
    }

    conv_G = (int**)malloc(R*sizeof(int*));
    for(i = 0; i < R ;i++){
        *(conv_G+i) = (int*)malloc(R*sizeof(int));
    }

    conv_B = (int**)malloc(R*sizeof(int*));
    for(i = 0; i < R ;i++){
        *(conv_B+i) = (int*)malloc(R*sizeof(int));
    }   

    Convolution(R,3,S,pad_R,Blur,conv_R);
    Convolution(R,3,S,pad_G,Blur,conv_G);
    Convolution(R,3,S,pad_B,Blur,conv_B);
*/


    //Blur 5X5
    int Blur[5][5] = {{1, 4, 6, 4, 1},{4, 16, 24, 16, 4},{6, 24, 36, 24, 6},{4, 16, 24, 16, 4},{1, 4, 6, 4, 1}};
    int R = ((W-5+2*P)/S)+1;

    conv_R = (int**)malloc(R*sizeof(int*));
    for(i = 0; i < R ;i++){
        *(conv_R+i) = (int*)malloc(R*sizeof(int));
    }

    conv_G = (int**)malloc(R*sizeof(int*));
    for(i = 0; i < R ;i++){
        *(conv_G+i) = (int*)malloc(R*sizeof(int));
    }

    conv_B = (int**)malloc(R*sizeof(int*));
    for(i = 0; i < R ;i++){
        *(conv_B+i) = (int*)malloc(R*sizeof(int));
    }   

    Convolution(R,5,S,pad_R,Blur,conv_R);
    Convolution(R,5,S,pad_G,Blur,conv_G);
    Convolution(R,5,S,pad_B,Blur,conv_B);


    Mat image_Edge(R,R,CV_8UC3);

    for(y=0; y<image_Edge.rows ; y++)
    {
        for(x=0 ; x<image_Edge.cols ; x++)
        {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y,x);
            image_Edge.at<cv::Vec3b>(y,x)[2] = conv_R[y][x]/256;
            image_Edge.at<cv::Vec3b>(y,x)[1] = conv_G[y][x]/256;
            image_Edge.at<cv::Vec3b>(y,x)[0] = conv_B[y][x]/256;
        }
    } 
    namedWindow("filter",WINDOW_AUTOSIZE);
    imshow("filter",image_Edge);

    waitKey(0);


    for(i = 0; i < W ;i++){
        free(*(aR+i));
        free(*(aG+i));
        free(*(aB+i));
    }

    for(i=0 ; i < (W+(2*P)) ; i++){
        free(*(pad_R+i));
        free(*(pad_G+i));
        free(*(pad_B+i));
    }

    for(i = 0; i < R ;i++){
        free(*(conv_R+i));
        free(*(conv_G+i));
        free(*(conv_B+i));
    }    

    free(aR);
    free(aG);
    free(aB);
    free(pad_R);
    free(pad_G);
    free(pad_B);
    free(conv_R);
    free(conv_G);
    free(conv_B);

}
