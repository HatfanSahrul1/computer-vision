#include <opencv2/opencv.hpp>
#include <iostream>

// using namespace std;
// using namespace cv;

int main(){
    cv::VideoCapture cap(0);
    cv::Mat frame;

    while(true){
        cap>>frame;

        if(frame.empty()){
            std::cout<<"End"<<std::endl;
            break;
        }

        cv::imshow("normal",frame);
    }
    return 0;
}