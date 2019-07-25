#include <stdio.h>
#include <stdlib.h>

int main()
{

	int i, j, ch;
	int ***p, ***pad,***conv;
	int P,S,W = 5;

	printf("Channel num : ");
	scanf("%d", &ch);
	printf("%d",ch);
/*
	p = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(p + i) = (int**)malloc(W*sizeof(int*));
		for (j = 0; j < W; j++){
			*(*(p + i) + j) = (int*)malloc(W*sizeof(int));
		}
	}

	int x, y, z;
	for (z = 0; z < ch; ch++){
		for (y = 0; y<W; y++){
			for (x = 0; x<W; x++){
				//cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
				p[z][y][x] = image.at<cv::Vec3b>(y, x)[z];  //B G R 
			}
		}
	}

	printf("Padding rate : ");
	scanf("%d", &P);

	printf("Stride value : ");
	scanf("%d", &S);

	pad = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(pad + i) = (int**)malloc((W + (2 * P)*sizeof(int*));
		for (j = 0; j < (W + (2 * P)); j++){
			*(*(pad + i) + j) = (int*)malloc((W + (2 * P)*sizeof(int));
		}
	}

	for (i = 0; i < ch; i++){
		make_padding(W, P, p[i], pad[i]);
	}

	Mat image_pad(image.rows + 2 * P, image.cols + 2 * P, CV_8UC3);

	for (z = 0; z < ch; z++){
		for (y = 0; y<image_pad.rows; y++){
			for (x = 0; x<image_pad.cols; x++){
				cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
				image_pad.at<cv::Vec3b>(y, x)[z] = pad[z][y][x];
			}
		}
	}


	conv = (int***)malloc(ch*sizeof(int**));

	for (i = 0; i < ch; i++){
		*(p + i) = (int**)malloc(R*sizeof(int*));
		for (j = 0; j < R; j++){
			*(*(p + i) + j) = (int*)malloc(R*sizeof(int));
		}
	}



	for (i = 0; i < ch; i++){
		for (j = 0; j < W; j++){
			for (int k = 0; k < W; k++){
				p[i][j][k] = 0;
			}
		}
	}

	for (i = 0; i < ch; i++){
		for (j = 0; j < W; j++){
			for (int k = 0; k < W; k++){
				printf("%d", p[i][j][k]);
			}
			printf("  ");
		}
		printf("\n");
	}




	for (i = 0; i < ch; i++){
		for (j = 0; j < W; j++){
			free(*(*(p + i) + j));
		}
		free(*(p + i));
	}
	free(p);

	for (i = 0; i < ch; i++){
		for (j = 0; j < (W + (2 * P)); j++){
			free(*(*(pad + i) + j));
		}
		free(*(pad + i));
	}
	free(pad);

	for (i = 0; i < ch; i++){
		for (j = 0; j < R; j++){
			free(*(*(conv + i) + j));
		}
		free(*(conv + i));
	}
	free(conv);

	*/
}


