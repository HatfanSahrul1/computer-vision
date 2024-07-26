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
    Mat colored;
    Coloring(skel, colored);
    Mat skelBinary;
    threshold(skel, skelBinary, 0, 255, THRESH_BINARY);

    vector<Vec4i> lines;
    HoughLinesP(skelBinary, lines, 1, CV_PI / 180, 50, 10, 10);

    // Draw the lines on the original image
    Mat imWithLines = im.clone();
    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        line(imWithLines, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
    }
    // namedWindow("Original Image", WINDOW_NORMAL);
    // namedWindow("Skeleton Image", WINDOW_NORMAL);
    imshow("Original Image", im);
    imshow("Skeleton Image", skel);
    imshow("colored Image", imWithLines);
    waitKey(0);

    return 0;

}