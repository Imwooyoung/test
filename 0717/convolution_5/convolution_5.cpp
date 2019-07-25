#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

void padding(int W, int P, int** input, int** padding);
void max_pooling(int R, int F, int S, int** input, int** pool);

//////////////////////////////// Activation ////////////////////////////////

double getActivation(double sigma)  //Activation Function
{
	//sigmoid function 1 / (1 + exp(-sigma));
	return sigma;
}

int*** Activation(int ch, int W, int P, int*** input)
{
    int i, j;
    int ***act;
    int x,y,z;

	act = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(act + i) = (int**)malloc((W + (2*P))*sizeof(int*));
		for (j = 0; j < (W + (2*P)) ; j++){
			*(*(act + i) + j) = (int*)malloc((W + (2*P))*sizeof(int));
		}
	}

	Mat image_act((W + (2*P)) , (W + (2*P)), CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<(W + (2*P)); y++){
			for (x = 0; x<(W + (2*P)); x++){
				image_act.at<cv::Vec3b>(y, x)[z] = getActivation((double)input[z][y][x]);
			}
		}
	}

    namedWindow("Activation",WINDOW_AUTOSIZE);
    imshow("Activation",image_act);

    return act;
}

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

void Convolution(int R, int F, int S, int** input, int** filter, int** conv)
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

int*** Edge_detect(int ch, int R, int S, int*** input, int** filter)
{
    int ***conv;
    int i, j;
    int x,y,z,temp;

	conv = (int***)malloc(ch*sizeof(int**));
	for (i = 0; i < ch; i++){
		*(conv + i) = (int**)malloc(R*sizeof(int*));
		for (j = 0; j < R; j++){
			*(*(conv + i) + j) = (int*)malloc(R*sizeof(int));
		}
	}

    clock_t begin = clock();

	for (i = 0; i < ch; i++){
		Convolution(R, 3, S, input[i], filter, conv[i]);
	}

    clock_t end = clock();
    double elapsed_secs = double(end - begin);
    printf("time : %.4f sec\n", elapsed_secs/CLOCKS_PER_SEC);

    Mat image_Edge(R,R,CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<image_Edge.rows; y++){
			for (x = 0; x<image_Edge.cols; x++){
                temp = conv[z][y][x];
                if(temp > 255){
                    temp = 255;
                }
                else if(temp<0){
                    temp = 0;
                }
				image_Edge.at<cv::Vec3b>(y, x)[z] = temp;
			}
		}
	}
    
    imwrite("test_edge.jpg",image_Edge);
    namedWindow("Edge Detect",WINDOW_AUTOSIZE);
    imshow("Edge Detect",image_Edge);

    return conv;
}

//////////////////////////////// Blur Effect ////////////////////////////////

int*** Blur_effect(int ch, int R, int S, int*** input, int** filter)
{
    int ***conv;
    int i, j;
    int x,y,z, temp;

	conv = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(conv + i) = (int**)malloc(R*sizeof(int*));
		for (j = 0; j < R; j++){
			*(*(conv + i) + j) = (int*)malloc(R*sizeof(int));
		}
	}

    clock_t begin = clock();

	for (i = 0; i < ch; i++){
		Convolution(R, 5, S, input[i], filter, conv[i]);
	}

    clock_t end = clock();
    double elapsed_secs = double(end - begin);
    printf("%.4f\n", elapsed_secs/CLOCKS_PER_SEC);

    Mat image_Blur(R,R,CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<image_Blur.rows; y++){
			for (x = 0; x<image_Blur.cols; x++){
                temp = conv[z][y][x]/256;
                if(temp > 255){
                    temp = 255;
                }
                else if(temp<0){
                    temp = 0;
                }
				image_Blur.at<cv::Vec3b>(y, x)[z] = temp;
			}
		}
	}
    
    imwrite("test_blur.jpg",image_Blur);
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
				image_max.at<cv::Vec3b>(y, x)[z] = pool[z][y][x];
			}
		}
	}
    
    imwrite("test_max.jpg",image_max);
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
    image = imread("test.jpg",IMREAD_COLOR);
    if(image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    //namedWindow("Original",WINDOW_AUTOSIZE);
    //imshow("Original",image);

    W = image.rows;
    ch = image.channels();

	p = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(p + i) = (int**)malloc(W*sizeof(int*));
		for (j = 0; j < W; j++){
			*(*(p + i) + j) = (int*)malloc(W*sizeof(int));
		}
	}
	
	for (z = 0; z < ch; z++){
		for (y = 0; y<W; y++){
			for (x = 0; x<W; x++){
				p[z][y][x] = image.at<cv::Vec3b>(y, x)[z];  //B G R 
			}
		}
	}

    printf("Padding rate : ");
	scanf("%d", &P);

	printf("Stride value : ");
	scanf("%d", &S);

    int R, mode=0;
    int **filter, ***act;
    int Edge[3][3] = {{-1, -1, -1},{-1, 8, -1},{-1, -1, -1}};
    int Blur[5][5] = {{1, 4, 6, 4, 1},{4, 16, 24, 16, 4},{6, 24, 36, 24, 6},{4, 16, 24, 16, 4},{1, 4, 6, 4, 1}};    

    //make padding image
    pad = make_padding(ch, W, P, p);

    while(1)
    {
        printf("< MODE >   1.Activation   2.Edge   3.Blur   4.max_pooling  : ");
        scanf("%d",&mode);   

        if(mode == 1)
        {
            act = Activation(ch, W, P, pad);

            for (i = 0; i < ch; i++){
		        for (j = 0; j < (W + (2*P)); j++){
			        free(*(*(act + i) + j));
		        }
		        free(*(act + i));
	        }
	        free(act);

            break;
        }
        else if(mode == 2)
        {
            F = 3;
            R = ((W-F+2*P)/S)+1; 

        	filter = (int**)malloc(ch*sizeof(int*));
	        for (i = 0; i < F; i++){
		        *(filter + i) = (int*)malloc(3*sizeof(int));
	        }

	        for (i = 0; i < F; i++){
		        for (j = 0; j < F; j++){
                    filter[i][j] = Edge[i][j];
		        }
	        }

            conv = Edge_detect(ch, R, S, pad, filter);
            break;  
        }
        else if(mode == 3)
        {
            F = 5;
            R = ((W-F+2*P)/S)+1;

            filter = (int**)malloc(F*sizeof(int*));
	        for (i = 0; i < F; i++){
		        *(filter + i) = (int*)malloc(F*sizeof(int));
	        }

	        for (i = 0; i < F; i++){
		        for (j = 0; j < F; j++){
                    filter[i][j] = Blur[i][j];
		        }
	        }    

            conv = Blur_effect(ch, R, S, pad, filter);
            break;        
        }
        else if(mode == 4)
        {
        	printf("F value : ");
	        scanf("%d", &F);

            R = ((W-F+2*P)/S)+1;
            conv = MAX_pooling(ch, R, F, P, S, pad);
            break;
        }
        else
        {
            printf("번호를 잘못 눌렀음!\n");
        }
    }

    waitKey(0);

    if(mode==2 & mode==3 & mode==4)
    {
        for (i = 0; i < F; i++){
		    free(*(filter + i));
	    }
        free(filter);   

	    for (i = 0; i < ch; i++){
		    for (j = 0; j < R; j++){
			    free(*(*(conv + i) + j));
		    }
		    free(*(conv + i));
	    }
	    free(conv);
    }

	for (i = 0; i < ch; i++){
		for (j = 0; j < W; j++){
			free(*(*(p + i) + j));
		}
		free(*(p + i));
	}
	free(p);    

	for (i = 0; i < ch; i++){
		for (j = 0; j < (W + (2*P)); j++){
			free(*(*(pad + i) + j));
		}
		free(*(pad + i));
	}
	free(pad);
}