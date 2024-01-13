#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main(){
    Mat img=imread("/home/hatfan/dataset/garis/frame_0.jpg",IMREAD_COLOR);
    Mat hsl;
    // for(int i=1;i<31;i=i+2){
    //     bilateralFilter(img,hsl,i,i*2,i/2);
    // }
    bilateralFilter(img,hsl,31,62,15);

    Mat gray;
    cvtColor(hsl,gray,COLOR_BGR2GRAY);

    std::vector<Point2f> corners;
    goodFeaturesToTrack(gray, corners, 100, 0.01, 10);

    // Draw points on the corners
    for (const auto& point : corners) {
        circle(hsl, point, 5, Scalar(0, 255, 0), -1);
    }

    imshow("s",hsl);

    waitKey();
    return 0;
}