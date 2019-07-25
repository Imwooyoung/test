#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

void padding(int W, int P, int** input, int** padding);
void max_pooling(int R, int F, int S, int** input, int** pool);


//////////////////////////////// Padding ////////////////////////////////
int*** make_padding(int ch, int W, int P, int*** input)
{
    int i,j;
    int ***pad;
    int x,y,z;

	pad = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(pad + i) = (int**)malloc((W + (2*P))*sizeof(int*));
		for (j = 0; j < (W + (2 * P)); j++){
			*(*(pad + i) + j) = (int*)malloc((W + (2*P))*sizeof(int));
		}
	}

	for (i = 0; i < ch; i++){
		padding(W, P, input[i], pad[i]);
	}    

	Mat image_pad(W + 2*P, W + 2*P, CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<image_pad.rows; y++){
			for (x = 0; x<image_pad.cols; x++){
				//cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
				image_pad.at<cv::Vec3b>(y, x)[z] = pad[z][y][x];
			}
		}
	}

    //imwrite("test_padding.jpg",image_pad);

    return pad;
}

void padding(int W, int P, int** input, int** padding)
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

//////////////////////////////// Convolution ////////////////////////////////

void Convolution(int R, int F, int S, int** input, int filter[][3], int** conv)
{
    int i, j, k;
    int m, n, sum;
    for(k=0 ; k< R*R; k++){
        m = S*(k/R);
        n = S*(k%R);
        sum = 0;
        for(i=0; i<F ; i++){
            for(j=0 ; j<F; j++){
                sum = sum + (input[m+i][n+j] * filter[i][j]);
            }
        }
        m = (k/R);
        n = (k%R);
        conv[m][n] = sum;
    }
}

void Convolution_B(int R, int F, int S, int** input, int filter[][5], int** conv)
{
    int i, j, k;
    int m, n, sum;
    for(k=0 ; k< R*R; k++){
        m = S*(k/R);
        n = S*(k%R);
        sum = 0;
        for(i=0; i<F ; i++){
            for(j=0 ; j<F; j++){
                sum = sum + (input[m+i][n+j] * filter[i][j]);
            }
        }
        m = (k/R);
        n = (k%R);
        conv[m][n] = sum;
    }
}

//////////////////////////////// Edge Detect ////////////////////////////////

int*** Edge_detect(int ch, int W, int P, int S, int*** input)
{
    int Edge[3][3] = {{-1, -1, -1},{-1, 8, -1},{-1, -1, -1}};
    int R = ((W-3+2*P)/S)+1;
    int ***conv;
    int i, j;
    int x,y,z;

	conv = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(conv + i) = (int**)malloc(R*sizeof(int*));
		for (j = 0; j < R; j++){
			*(*(conv + i) + j) = (int*)malloc(R*sizeof(int));
		}
	}

    clock_t begin = clock();

	for (i = 0; i < ch; i++){
		Convolution(R, 3, S, input[i], Edge, conv[i]);
	}

    clock_t end = clock();
    double elapsed_secs = double(end - begin);
    printf("%.4f\n", elapsed_secs/CLOCKS_PER_SEC);

    Mat image_Edge(R,R,CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<image_Edge.rows; y++){
			for (x = 0; x<image_Edge.cols; x++){
				//cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
				image_Edge.at<cv::Vec3b>(y, x)[z] = conv[z][y][x]/256;
			}
		}
	}
    
    //imwrite("test_edge.jpg",image_Edge);
    namedWindow("Edge Detect",WINDOW_AUTOSIZE);
    imshow("Edge Detect",image_Edge);

    return conv;
}

//////////////////////////////// Blur Effect ////////////////////////////////

int*** Blur_effect(int ch, int W, int P, int S, int*** input)
{
    int Blur[5][5] = {{1, 4, 6, 4, 1},{4, 16, 24, 16, 4},{6, 24, 36, 24, 6},{4, 16, 24, 16, 4},{1, 4, 6, 4, 1}};
    int R = ((W-5+2*P)/S)+1;
    int ***conv;
    int i, j;
    int x,y,z;

	conv = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(conv + i) = (int**)malloc(R*sizeof(int*));
		for (j = 0; j < R; j++){
			*(*(conv + i) + j) = (int*)malloc(R*sizeof(int));
		}
	}

    clock_t begin = clock();

	for (i = 0; i < ch; i++){
		Convolution_B(R, 5, S, input[i], Blur, conv[i]);
	}

    clock_t end = clock();
    double elapsed_secs = double(end - begin);
    printf("%.4f\n", elapsed_secs/CLOCKS_PER_SEC);

    Mat image_Blur(R,R,CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<image_Blur.rows; y++){
			for (x = 0; x<image_Blur.cols; x++){
				//cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
				image_Blur.at<cv::Vec3b>(y, x)[z] = conv[z][y][x]/256;
			}
		}
	}
    
    //imwrite("test_blur.jpg",image_Blur);
    namedWindow("Blur_effect",WINDOW_AUTOSIZE);
    imshow("Blur_effect",image_Blur);

    return conv;
}

//////////////////////////////// Max Pooling ////////////////////////////////

int*** MAX_pooling(int ch, int R, int F, int P, int S, int*** input)
{
    int ***pool;
    int i, j;
    int x,y,z;

	pool = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(pool + i) = (int**)malloc(R*sizeof(int*));
		for (j = 0; j < R; j++){
			*(*(pool + i) + j) = (int*)malloc(R*sizeof(int));
		}
	}

    clock_t begin = clock();

	for (i = 0; i < ch; i++){
		max_pooling(R, F, S, input[i], pool[i]);
	}

    clock_t end = clock();
    double elapsed_secs = double(end - begin);
    printf("%.4f\n", elapsed_secs/CLOCKS_PER_SEC);

    Mat image_max(R,R,CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<image_max.rows; y++){
			for (x = 0; x<image_max.cols; x++){
				//cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
				image_max.at<cv::Vec3b>(y, x)[z] = pool[z][y][x];
			}
		}
	}
    
    //imwrite("test_max.jpg",image_max);
    namedWindow("Max pooling",WINDOW_AUTOSIZE);
    imshow("Max pooling",image_max);

    return pool;
}

void max_pooling(int R, int F, int S, int** input, int** pool)
{
    int i,j,k;
    int m=0,n=0,max;
    for(k=0 ; k< R*R; k++){
        m = S*(k/R);
        n = S*(k%R);
        max = 0;
        for(i=0; i<F ; i++){
            for(j=0 ; j<F; j++){
                if(max < input[m+i][n+j]){
                    max = input[m+i][n+j];
                }
            }
        }
        m = (k/R);
        n = (k%R);
        pool[m][n] = max;
    }
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////// Main ////////////////////////////////
//////////////////////////////////////////////////////////////////////

int main()
{
    int i, j, ch;
	int ***p, ***pad,***conv;
	int W,F,P,S;
    int x, y, z;

    Mat image;
    image = imread("tree.jpg",IMREAD_COLOR);
    if(image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }


    W = image.rows;

	ch = image.channels();

	p = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(p + i) = (int**)malloc(W*sizeof(int*));
		for (j = 0; j < W; j++){
			*(*(p + i) + j) = (int*)malloc(W*sizeof(int));
		}
	}
	
	z=2;
	for (y = 0; y<W; y++){
		for (x = 0; x<W; x++){
			p[z][y][x] = image.at<cv::Vec3b>(y, x)[z];  //B G R 
		}
	}


    	Mat image_test(W,W,CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<image_test.rows; y++){
			for (x = 0; x<image_test.cols; x++){
				image_test.at<cv::Vec3b>(y, x)[z] = p[z][y][x];
			}
		}
	}
	imwrite("tree red.jpg",image_test);
	namedWindow("test",WINDOW_AUTOSIZE);
	imshow("test",image_test);

	for (i = 0; i < ch; i++){
		for (j = 0; j < W; j++){
			free(*(*(p + i) + j));
		}
		free(*(p + i));
	}
	free(p);  
	
    waitKey(0);
}
