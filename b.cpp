#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    VideoCapture cap(0);
    Mat frame;
    if(!cap.isOpened()){
        cout<<"video dont start"<<endl;
        return -1;
    }

    Scalar lowOren=Scalar(0,100, 100);
    Scalar uppOren=Scalar(20,255,255);

    while(true){
        cap>>frame;

        if(frame.empty()){
            cout<<"End"<<endl;
            break;
        }

        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        
        Mat mask;
        inRange(hsv,lowOren,uppOren,mask);

        imshow("normal",frame);
        imshow("hp",mask);
    }
    return 0;
}