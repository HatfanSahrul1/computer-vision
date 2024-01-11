#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat frame=imread("/home/hatfan/test2/bolaBanyak.png",1);
    
     if (frame.empty()) {
        cerr << "Error: Couldn't open the image." << endl;
        return -1;
    }

    Scalar lowerOrange = Scalar(0, 100, 100);
    Scalar upperOrange = Scalar(20, 255, 255);

    namedWindow("Ball Detection", WINDOW_NORMAL);
    namedWindow("bw", WINDOW_GUI_EXPANDED);

    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);

    Mat mask;
    inRange(hsv,lowerOrange,upperOrange,mask);

    Scalar red(255,0,0);
    frame.setTo(red,mask);
    imshow("img",frame);

    waitKey();

    return 0;
}