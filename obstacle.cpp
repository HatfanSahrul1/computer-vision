#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "iostream"

using namespace std;
using namespace cv;

int main(int argc, char** aegv){
    VideoCapture cap(0);
    Mat frame(480, 640, CV_8UC3);

    while(true){
        cap >>frame;
        resize(frame,frame, Size(640,480));
        line(frame, Point(319,0), Point(319, 479), Scalar(0, 255, 0), 1, LINE_4);
        line(frame, Point(0,239), Point(659, 239), Scalar(0, 255, 0), 1, LINE_4);

        line(frame, Point(159,0), Point(159, 239), Scalar(180, 180, 0), 1, LINE_4);
        line(frame, Point(479,0), Point(479, 239), Scalar(180, 180, 0), 1, LINE_4);
        
        
        imshow("i", frame);
        if(waitKey(30)==27) break;
    }
}
