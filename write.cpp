#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat img=imread("/home/hatfan/test2/key1.jpg", IMREAD_COLOR);

    imwrite("key1",img);
}