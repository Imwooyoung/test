#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

void padding(int W, int C, int P, int** input, int** padding);
void max_pooling(int Rw, int Rc, int F, int S, int** input, int** pool);

//////////////////////////////// Activation ////////////////////////////////
double getActivation(double sigma)  //Activation Function
{
	//sigmoid function
	return sigma; //1/(1 + exp(-sigma));
}

int*** Activation(int ch, int W, int C, int P, int*** input)
{
    int i, j;
    int ***act;
    int x,y,z;

	act = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(act + i) = (int**)malloc((W + (2*P))*sizeof(int*));
		for (j = 0; j < (W + (2*P)) ; j++){
			*(*(act + i) + j) = (int*)malloc((C + (2*P))*sizeof(int));
		}
	}

	Mat image_act((W + (2*P)) , (C + (2*P)), CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<(W + (2*P)); y++){
			for (x = 0; x<(C + (2*P)); x++){
				image_act.at<cv::Vec3b>(y, x)[z] = getActivation((double)input[z][y][x]);
			}
		}
	}

    namedWindow("Activation",WINDOW_AUTOSIZE);
    imshow("Activation",image_act);

    return act;
}

//////////////////////////////// Padding ////////////////////////////////
int*** make_padding(int ch, int W, int C, int P, int*** input)
{
    int i,j;
    int ***pad;
    int x,y,z;

	pad = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(pad + i) = (int**)malloc((W + (2*P))*sizeof(int*));
		for (j = 0; j < (W + (2 * P)); j++){
			*(*(pad + i) + j) = (int*)malloc((C + (2*P))*sizeof(int));
		}
	}

	for (i = 0; i < ch; i++){
		padding(W, C, P, input[i], pad[i]);
	}    

	Mat image_pad(W + 2*P, C + 2*P, CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<image_pad.rows; y++){
			for (x = 0; x<image_pad.cols; x++){
				image_pad.at<cv::Vec3b>(y, x)[z] = pad[z][y][x];
			}
		}
	}

    //imwrite("test_padding.jpg",image_pad);
    //namedWindow("padding",WINDOW_AUTOSIZE);
    //imshow("padding",image_pad);
    return pad;
}

void padding(int W, int C, int P, int** input, int** padding)
{
    int i,j;

    for(i=0 ; i<P ; i++){
        for(j=0 ; j<(C+(2*P)) ; j++){
                padding[i][j] = 0;
        }   
    }

    for(i=P ; i< (W+P) ; i++){
        for(j=0 ; j<P ; j++){
            padding[i][j] = 0;
        }

        for(j=P ; j<C+P ; j++){
            padding[i][j] = input[i-P][j-P];
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
}

//////////////////////////////// Convolution ////////////////////////////////
void Convolution(int Rw, int Rc, int F, int S, int** input, int** filter, int** conv)
{
    int i, j, k, m, n, sum;

    for(m=0 ; m< Rw ; m++){
        for(n=0 ; n < Rc ; n++){
            sum = 0;
            for(i=0; i<F ; i++){
                for(j=0 ; j<F; j++){
                    sum = sum + (input[m*S+i][n*S+j] * filter[i][j]);
                }
            }
            conv[m][n] = sum;
        }
    }
}

//////////////////////////////// Edge Detect ////////////////////////////////
int*** Edge_detect(Mat src, int ch, int Rw, int Rc, int W, int C, int S, int*** input, int** filter)
{
    int ***conv;
    int i, j;
    int x,y,z,temp;

	conv = (int***)malloc(ch*sizeof(int**));
	for (i = 0; i < ch; i++){
		*(conv + i) = (int**)malloc(Rw*sizeof(int*));
		for (j = 0; j < Rw; j++){
			*(*(conv + i) + j) = (int*)malloc(Rc*sizeof(int));
		}
	}

    clock_t begin = clock();

	for (i = 0; i < ch; i++){
		Convolution(Rw, Rc, 3, S, input[i], filter, conv[i]);
	}

    clock_t end = clock();
    double elapsed_secs = double(end - begin);
    printf("time : %.4f sec\n", elapsed_secs/CLOCKS_PER_SEC);

    Mat image_Edge(Rw,Rc,CV_8UC3);

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

    //imwrite("test_edge.jpg",image_Edge);
    //namedWindow("Edge Detect",WINDOW_AUTOSIZE);
    //imshow("Edge Detect",image_Edge);

    Mat dst;
    int temp2;

    Mat kernel = (Mat_<int>(3,3) << -1,-1,-1,-1,8,-1,-1,-1,-1);
    filter2D( src, dst, -1 , kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );  

	for (z = 0; z < ch; z++){
		for (y = 0; y<Rw; y++){
			for (x = 0; x<Rc; x++){
				temp2 = image_Edge.at<cv::Vec3b>(y, x)[z] - dst.at<cv::Vec3b>(y, x)[z];  //B G R 
                if(temp2 < 0) temp2 = 0;
                dst.at<cv::Vec3b>(y, x)[z] = temp2;
			}
		}
	} 
       
    namedWindow( "filter2D Demo sub", CV_WINDOW_AUTOSIZE );
    imshow( "filter2D Demo sub", dst );   

    return conv;
}

//////////////////////////////// Blur Effect ////////////////////////////////
int*** Blur_effect(int ch, int Rw, int Rc, int S, int*** input, int** filter)
{
    int ***conv;
    int i, j;
    int x,y,z, temp;

	conv = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(conv + i) = (int**)malloc(Rw*sizeof(int*));
		for (j = 0; j < Rw; j++){
			*(*(conv + i) + j) = (int*)malloc(Rc*sizeof(int));
		}
	}

    clock_t begin = clock();

	for (i = 0; i < ch; i++){
		Convolution(Rw, Rc, 5, S, input[i], filter, conv[i]);
	}

    clock_t end = clock();
    double elapsed_secs = double(end - begin);
    printf("time : %.4f sec\n", elapsed_secs/CLOCKS_PER_SEC);

    Mat image_Blur(Rw,Rc,CV_8UC3);

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
    
    //imwrite("test_blur.jpg",image_Blur);
    namedWindow("Blur_effect",WINDOW_AUTOSIZE);
    imshow("Blur_effect",image_Blur);   
    return conv;
}

//////////////////////////////// Max Pooling ////////////////////////////////
int*** MAX_pooling(int ch, int Rw, int Rc, int F, int P, int S, int*** input)
{
    int ***pool;
    int i, j;
    int x,y,z;

	pool = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(pool + i) = (int**)malloc(Rw*sizeof(int*));
		for (j = 0; j < Rw; j++){
			*(*(pool + i) + j) = (int*)malloc(Rc*sizeof(int));
		}
	}

    clock_t begin = clock();

	for (i = 0; i < ch; i++){
		max_pooling(Rw, Rc, F, S, input[i], pool[i]);
	}

    clock_t end = clock();
    double elapsed_secs = double(end - begin);
    printf("time : %.4f sec\n", elapsed_secs/CLOCKS_PER_SEC);

    Mat image_max(Rw,Rc,CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<image_max.rows; y++){
			for (x = 0; x<image_max.cols; x++){
				image_max.at<cv::Vec3b>(y, x)[z] = pool[z][y][x];
			}
		}
	}
    
    //imwrite("test_max.jpg",image_max);
    namedWindow("Max pooling",WINDOW_AUTOSIZE);
    imshow("Max pooling",image_max);
    return pool;
}

void max_pooling(int Rw, int Rc, int F, int S, int** input, int** pool)
{
    int i, j, k, m, n, max;

    for(m=0 ; m< Rw ; m++){
        for(n=0 ; n < Rc ; n++){
            max = 0;
            for(i=0; i<F ; i++){
                for(j=0 ; j<F; j++){
                    if(max < input[m*S+i][n*S+j]){
                        max = input[m*S+i][n*S+j];
                    }
                }
            }
            pool[m][n] = max;
        }
    }
}
/*
void MyBlur(const Mat& input, Mat& output, const Size& size)
{
    Mat kernel(size,CV_32F,Scalar(1.0/size.area()));
    filter2D(input, output, input.depth(),kernal);
}
*/

void conv2( cv::Mat src, int ch, int W, int C, int***conv)
{
    int x, y, z;
    cv::Mat dst;
    //kernel = cv::Mat::ones( kernel_size, kernel_size, CV_32F ) / (float)( kernel_size * kernel_size );
    Mat kernel = (Mat_<int>(3,3) << -1,-1,-1,-1,8,-1,-1,-1,-1);
    /// Apply filter
    cv::filter2D( src, dst, -1 , kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );

	for (z = 0; z < ch; z++){
		for (y = 0; y<W; y++){
			for (x = 0; x<C; x++){
				dst.at<cv::Vec3b>(y, x)[z] = dst.at<cv::Vec3b>(y, x)[z] - conv[z][y][x];  //B G R 
			}
		}
	} 

    cv::namedWindow( "filter2D Demo", CV_WINDOW_AUTOSIZE );
    cv::imshow( "filter2D Demo", dst );
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////// Main ////////////////////////////////
//////////////////////////////////////////////////////////////////////
int main()
{
    int i, j, ch;
	int ***p, ***pad,***conv;
	int W,C,F,P,S;
    int x, y, z;

    Mat image;
    image = imread("tree2.jpg",IMREAD_COLOR);
    if(image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    W = image.rows;
    C = image.cols;
    ch = image.channels();

//    Mat edge;
  //  Canny(image,edge,130,210,3); // Canny 연산




    //Mat Blurred;
    //blur(image, Blurred, Size(5,5));



 
    //imshow("Canny Image", edge);
    //namedWindow("Original",WINDOW_AUTOSIZE);
    //imshow("Original",image); 





	p = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(p + i) = (int**)malloc(W*sizeof(int*));
		for (j = 0; j < W; j++){
			*(*(p + i) + j) = (int*)malloc(C*sizeof(int));
		}
	}
	
	for (z = 0; z < ch; z++){
		for (y = 0; y<W; y++){
			for (x = 0; x<C; x++){
				p[z][y][x] = image.at<cv::Vec3b>(y, x)[z];  //B G R 
			}
		}
	}



    printf("Padding rate : ");
	scanf("%d", &P);

	printf("Stride value : ");
	scanf("%d", &S);

    int Rw, Rc, mode=0;
    int **filter, ***act;
    int Edge[3][3] = {{-1, -1, -1},{-1, 8, -1},{-1, -1, -1}};
    int Blur[5][5] = {{1, 4, 6, 4, 1},{4, 16, 24, 16, 4},{6, 24, 36, 24, 6},{4, 16, 24, 16, 4},{1, 4, 6, 4, 1}};    

    //make padding image
    pad = make_padding(ch, W, C, P, p);

    while(1)
    {
        printf("< MODE >   1.Activation   2.Edge   3.Blur   4.max_pooling  : ");
        scanf("%d",&mode);   

        if(mode == 1)
        {
            act = Activation(ch, W, C, P, pad);

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
            Rw = ((W-F+2*P)/S)+1;
            Rc = ((C-F+2*P)/S)+1;

        	filter = (int**)malloc(ch*sizeof(int*));
	        for (i = 0; i < F; i++){
		        *(filter + i) = (int*)malloc(F*sizeof(int));
	        }

	        for (i = 0; i < F; i++){
		        for (j = 0; j < F; j++){
                    filter[i][j] = Edge[i][j];
		        }
	        }


            conv = Edge_detect(image, ch, Rw, Rc, W, C, S, pad, filter);
         

            break;  
        }
        else if(mode == 3)
        {
            F = 5;
            Rw = ((W-F+2*P)/S)+1;
            Rc = ((C-F+2*P)/S)+1;

            filter = (int**)malloc(F*sizeof(int*));
	        for (i = 0; i < F; i++){
		        *(filter + i) = (int*)malloc(F*sizeof(int));
	        }

	        for (i = 0; i < F; i++){
		        for (j = 0; j < F; j++){
                    filter[i][j] = Blur[i][j];
		        }
	        }    

            conv = Blur_effect(ch, Rw, Rc, S, pad, filter);


            break;        
        }
        else if(mode == 4)
        {
        	printf("F value : ");
	        scanf("%d", &F);

            Rw = ((W-F+2*P)/S)+1;
            Rc = ((C-F+2*P)/S)+1;
            conv = MAX_pooling(ch, Rw, Rc, F, P, S, pad);
            break;
        }
        else
        {
            printf("번호를 잘못 눌렀음!\n");
        }
    }

    //namedWindow("Blurred Image",WINDOW_AUTOSIZE); 
    //imshow("Blurred Image",Blurred);

    waitKey(0);

    if(mode==2 & mode==3 & mode==4)
    {
        for (i = 0; i < F; i++){
		    free(*(filter + i));
	    }
        free(filter);   

	    for (i = 0; i < ch; i++){
		    for (j = 0; j < Rw; j++){
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