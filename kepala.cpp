#include <opencv2/opencv.hpp>

using namespace cv;

int x, y, z;

int main(){
    namedWindow("sudut kepala",WINDOW_NORMAL);
    createTrackbar("sumbu_x", "sudut kepala", nullptr, 90, NULL);
    createTrackbar("sumbu_y", "sudut kepala", nullptr, 90, NULL);
    // createTrackbar("sumbu_z", "sudut kepala", nullptr, 90, NULL);

    setTrackbarPos("sumbu_x","sudut kepala",x);
    setTrackbarPos("sumbu_x","sudut kepala",y);
    // setTrackbarPos("sumbu_x","sudut kepala",z);

    Mat frame=Mat::zeros(480, 640, CV_8UC3);

    while(true){
        imshow("s", frame);
        if(waitKey(30)==27)
            break;;
    }
}