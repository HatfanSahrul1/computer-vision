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

    vector<Vec2f> lines;
    HoughLines(skelBinary, lines, 1, CV_PI / 180, 100);  // Adjust the threshold as needed

    // Draw the lines on the original image
    Mat imWithLines = im.clone();
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(imWithLines, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
    }
    // namedWindow("Original Image", WINDOW_NORMAL);
    // namedWindow("Skeleton Image", WINDOW_NORMAL);
    imshow("Original Image", im);
    imshow("Skeleton Image", skel);
    imshow("colored Image", imWithLines);
    waitKey(0);

    return 0;

}