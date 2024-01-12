#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat img=imread("/home/hatfan/test2/key1.jpg",0);

    cout<<img<<endl;

    return 0;
}