#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

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

    int x,y;


    for(y=0; y<image.rows ; y++)
    {
        for(x=0 ; x<image.cols ; x++)
        {

            Vec3b* pixel = image.ptr<Vec3b>(y);
            pixel[x][2] = pixel[x][2]/2;
            pixel[x][1] = pixel[x][1]/3;
            pixel[x][0] = pixel[x][0];

            /*
            cv::Vec3b pixel = image.at<cv::Vec3b>(y,x);
            image.at<cv::Vec3b>(y,x)[2] = image.at<cv::Vec3b>(y,x)[2]/2;
            image.at<cv::Vec3b>(y,x)[1] = image.at<cv::Vec3b>(y,x)[1]/3;
            image.at<cv::Vec3b>(y,x)[0] = image.at<cv::Vec3b>(y,x)[0];
            */
        }
    }

    namedWindow("Original2",WINDOW_AUTOSIZE);
    imshow("Original2",image);

    waitKey(0);
}