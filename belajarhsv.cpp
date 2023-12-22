#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image=imread("/home/hatfan/test2/bolaBanyak.png",1);
    
    Scalar lowOren=Scalar(0,100,100);
    Scalar highOren=Scalar(20,255,255);

    namedWindow("frame",WINDOW_AUTOSIZE);
    namedWindow("hsv",WINDOW_AUTOSIZE);
    namedWindow("bw",WINDOW_AUTOSIZE);

//for rdfsdfs
    Mat hsv;
    cvtColor(image,hsv,COLOR_BGR2HSV);

    Mat mask;
    inRange(image,lowOren,highOren,mask);

 
    imshow("frame",image);
    imshow("hsv",hsv);
    imshow("bw",mask);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
