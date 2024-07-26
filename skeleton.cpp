#include <iostream>
#include <opencv2/opencv.hpp>
#include "skeleton.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

    // if(argc!=2)
    // {
    //     cout<<"Need 2 arguments"<<endl;
    //     return -1;
    // }

    Mat im = imread("/home/hatfan/fokusL/mask/cap_mask_195.jpg");
    Mat skel = skeletonization(im);
    Mat colored, mask = Mat::zeros(im.size(), CV_8UC3);
    Coloring(skel, colored);

    // bitwise_not(im, mask, colored);

    // namedWindow("Original Image", WINDOW_NORMAL);
    // namedWindow("Skeleton Image", WINDOW_NORMAL);
    imshow("Original Image", im);
    imshow("Skeleton Image", skel);
    imshow("colored Image", mask);
    waitKey(0);

    return 0;

}