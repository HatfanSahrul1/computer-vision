#include "iostream"
#include "opencv4/opencv2/opencv.hpp"
#include "opencv4/opencv2/ximgproc.hpp"
#include "vector"

using namespace std;
using namespace cv;

void zhangSuenThinning(Mat& im) {
    im /= 255;
    Mat prev = Mat::zeros(im.size(), CV_8UC1);
    Mat diff;

    do {
        // Iterasi pertama
        Mat mFlag = Mat::zeros(im.size(), CV_8UC1);
        for (int i = 1; i < im.rows - 1; i++) {
            for (int j = 1; j < im.cols - 1; j++) {
                uchar p2 = im.at<uchar>(i - 1, j);
                uchar p3 = im.at<uchar>(i - 1, j + 1);
                uchar p4 = im.at<uchar>(i, j + 1);
                uchar p5 = im.at<uchar>(i + 1, j + 1);
                uchar p6 = im.at<uchar>(i + 1, j);
                uchar p7 = im.at<uchar>(i + 1, j - 1);
                uchar p8 = im.at<uchar>(i, j - 1);
                uchar p9 = im.at<uchar>(i - 1, j - 1);
                
                int A = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) + 
                        (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
                        (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
                        (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
                int B = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
                int m1 = p2 * p4 * p6;
                int m2 = p4 * p6 * p8;
                
                if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0) {
                    mFlag.at<uchar>(i, j) = 1;
                }
            }
        }
        im &= ~mFlag;

        // Iterasi kedua
        mFlag = Mat::zeros(im.size(), CV_8UC1);
        for (int i = 1; i < im.rows - 1; i++) {
            for (int j = 1; j < im.cols - 1; j++) {
                uchar p2 = im.at<uchar>(i - 1, j);
                uchar p3 = im.at<uchar>(i - 1, j + 1);
                uchar p4 = im.at<uchar>(i, j + 1);
                uchar p5 = im.at<uchar>(i + 1, j + 1);
                uchar p6 = im.at<uchar>(i + 1, j);
                uchar p7 = im.at<uchar>(i + 1, j - 1);
                uchar p8 = im.at<uchar>(i, j - 1);
                uchar p9 = im.at<uchar>(i - 1, j - 1);
                
                int A = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) + 
                        (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
                        (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
                        (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
                int B = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
                int m1 = p2 * p4 * p8;
                int m2 = p2 * p6 * p8;
                
                if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0) {
                    mFlag.at<uchar>(i, j) = 1;
                }
            }
        }
        im &= ~mFlag;
        
        absdiff(im, prev, diff);
        im.copyTo(prev);
    } while (countNonZero(diff) > 0);

    im *= 255;
}

int main(){
    cv::Mat frame=cv::imread("/home/hatfan/fokusL/mask/cap_mask_2676.jpg",0);
    cv::threshold(frame, frame, 127, 255, cv::THRESH_BINARY);
    cv::Mat skel(frame.size(), CV_8UC1, cv::Scalar(0));
    cv::Mat temp, eroded, edge;

    cv::Canny(frame, edge, 50, 150);
    // cv::erode(frame, eroded, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3)));
    // cv::dilate(eroded, temp, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3)));
    
    zhangSuenThinning(edge);

    cv::imshow("normal", frame);
    cv::imshow("thin", edge);

    cv::waitKey(0);
    return 0;
}