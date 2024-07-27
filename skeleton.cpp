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

    Mat im = imread("/home/hatfan/T_2/mask/cap_mask_3019.jpg");
    Mat skel = skeletonization(im);
    
    // Mat colored;
    // Coloring(skel, colored);
    // Mat skelBinary;
    // threshold(skel, skelBinary, 0, 255, THRESH_BINARY);
    // Mat imWithLines = im.clone();
    // Mat imWithLines=Mat::zeros(im.size(), CV_8UC3);
    
    // HoughlineRegular(skelBinary, imWithLines, atoi(argv[1]));
    // HoughlineProb(skelBinary, imWithLines, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    

    imshow("Original Image", im);
    imshow("Skeleton Image", skel);
    // imshow("colored Image", imWithLines);
    waitKey(0);

    return 0;

}