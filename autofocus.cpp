#include "opencv4/opencv2/opencv.hpp"

int main(){
    cv::VideoCapture cap(0);
    cv::Mat frame;
    // cap.Open();

    while(true){
    cap.set(cv::CAP_PROP_SETTINGS, 1);
        cap>>frame;
        cv::imshow("s", frame);
        if(cv::waitKey(30)==27) break;
    }
}