#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Point 

int main(){
    
    waitKey(0);
    return 0;
}


void roiPart1(){
    Mat img=imread("/home/hatfan/test2/test.jpg",1);
    Mat roi;

    Rect rect(img.cols/4,img.rows/4, img.cols/2,img.rows/2);

    rectangle(img,rect,Scalar(255),2,8,0);

    imshow("img",img);

    roi=img(rect);

    imshow("img2",roi);

}