#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

////////////////////////////// Show image //////////////////////////////
void show_image(int ch, int row, int col, int***input)
{
    int x,y,z;
	Mat image_show(row, col, CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y < row; y++){
			for (x = 0; x < col; x++){
                if(input[z][y][x] < 0) input[z][y][x] = 0;
                else if(input[z][y][x] > 255) input[z][y][x] = 255;
				image_show.at<cv::Vec3b>(y, x)[z] = input[z][y][x];
			}
		}
	}
    namedWindow("result",WINDOW_AUTOSIZE);
    imshow("result",image_show);
}

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

	for (z = 0; z < ch; z++){
		for (y = 0; y < (W + (2*P)); y++){
			for (x = 0; x < (W + (2*P)); x++){
				input[z][y][x] = getActivation(input[z][y][x]);
			}
		}
	}    

    show_image(ch, W + 2*P, C + 2*P, input);
    return act;
}

//////////////////////////////// Padding ////////////////////////////////
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

    show_image(ch, W + 2*P, C + 2*P,pad);
    return pad;
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

    show_image(ch,Rw,Rc,conv);
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
 
 	for (z = 0; z < ch; z++){
		for (y = 0; y<Rw; y++){
			for (x = 0; x<Rc; x++){
				conv[z][y][x] = conv[z][y][x]/256;
			}
		}
	}
    show_image(ch,Rw,Rc,conv);
    return conv;
}

//////////////////////////////// Max Pooling ////////////////////////////////
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

    show_image(ch,Rw,Rc,pool);
    return pool;
}

///////////////////////////////////// Main /////////////////////////////////////
int main()
{
    int i, j, ch;
	int ***p, ***pad,***conv, **filter, ***act;
	int W, C, F, P, S, type;
    int x, y, z;

    Mat image;
    image = imread("test.jpg",IMREAD_COLOR);
    if(image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    namedWindow("original",WINDOW_AUTOSIZE);
    imshow("original",image);

    W = image.rows;
    C = image.cols;
    ch = image.channels();
    type = image.type();

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