#include "iostream"
#include "opencv4/opencv2/opencv.hpp"
#include "opencv4/opencv2/ximgproc.hpp"
#include "vector"

int main(){
    cv::Mat frame=cv::imread("/home/hatfan/fokusL/mask/cap_mask_2676.jpg",0);
    cv::threshold(frame, frame, 127, 255, cv::THRESH_BINARY);
    cv::Mat skel(frame.size(), CV_8UC1, cv::Scalar(0));
    cv::Mat temp, eroded;

    bool done;
    // do{
        cv::erode(frame, eroded, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3)));
        cv::dilate(eroded, temp, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3)));
        cv::subtract(frame, temp, temp);
        cv::bitwise_or(skel, temp, skel);
        eroded.copyTo(frame);

        done=(cv::countNonZero(frame)==0);
    // }while(!done);

    cv::imshow("normal", eroded);
    cv::imshow("thin", temp);

    cv::waitKey(0);
    return 0;
}