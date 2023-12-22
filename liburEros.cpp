#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    VideoCapture cap(0);
    Mat frame;

    namedWindow("Tugas Deteksi Bola",WINDOW_AUTOSIZE);

    Mat gambar=imread("/home/hatfan/test2/bolaBanyak.png",1);
    waitKey(1);
    imshow("bola oren",gambar);

    for(;;){
        cap.read(frame);

        imshow("Tugas Deteksi Bola", frame);

        if(waitKey(1)==27)break;
    }

    cap.release();
    destroyAllWindows();
}