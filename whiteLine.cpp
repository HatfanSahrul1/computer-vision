#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void onTrackbar(int, void*){

}

int WL_H=20,WL_S=0,WL_V=200;
int WH_H=225,WH_S=150,WH_V=255;

int main(){
    VideoCapture cap(0);
    const string videoStreamAddress = "https://10.252.133.72:8080/videofeed?something.mjpeg";
    cap.open(videoStreamAddress);

    namedWindow("white",WINDOW_NORMAL);
    createTrackbar("wLow_H","white",&WL_H,255,onTrackbar);
    createTrackbar("wHigh_H","white",&WH_H,255,onTrackbar);
    createTrackbar("wLow_S","white",&WL_S,255,onTrackbar);
    createTrackbar("wHigh_S","white",&WH_S,255,onTrackbar);
    createTrackbar("wLow_V","white",&WL_V,255,onTrackbar);
    createTrackbar("wHigh_V","white",&WH_V,255,onTrackbar);

    Mat frm;

    while(true){
        cap>>frm;

        Mat hsv;
        cvtColor(frm,hsv,COLOR_BGR2HSV);

        Mat mask;
        inRange(hsv,Scalar(WL_H,WL_S,WL_V),Scalar(WH_H,WH_S,WH_V),mask);

        imshow("wh",mask);

        if(waitKey(30)==27) break;

    }
    return 0;
}