#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void onTrackbar(int, void*);

int lowH=0,lowS=100,lowV=100;//lowV 130 lymayan stabil
int highH=20,highS=255,highV=255;
int a=8,b=100;


int main() {
    VideoCapture cap(0);
    const string videoStreamAddress = "https://10.252.133.72:8080/videofeed?something.mjpeg";
    if (!cap.open(videoStreamAddress)) {
        cout << "Error opening the camera." << endl;
        return -1;
    }
        namedWindow("Detect",WINDOW_AUTOSIZE);
        namedWindow("set",WINDOW_AUTOSIZE);

        createTrackbar("lowH","set",&lowH,255,onTrackbar);
        createTrackbar("highH","set",&highH,255,onTrackbar);
        createTrackbar("lowS","set",&lowS,255,onTrackbar);
        createTrackbar("highS","set",&highS,255,onTrackbar);
        createTrackbar("lowV","set",&lowV,255,onTrackbar);
        createTrackbar("highV","set",&highV,255,onTrackbar);
        createTrackbar("hA","set",&a,20,onTrackbar);
        createTrackbar("hB","set",&b,300,onTrackbar);

       

    while (true) {
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            cout << "End of video stream" << endl;
            break;
        }

        
        
        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        Scalar lowOrange = Scalar(lowH, lowS, lowV);
        Scalar upOrange = Scalar(highH,highS,highV);

        Mat Mask;
        inRange(hsv, lowOrange, upOrange, Mask);

        GaussianBlur(Mask, Mask, Size(9, 9), 2, 2);

        vector<Vec3f> circles;
        HoughCircles(Mask, circles, HOUGH_GRADIENT, 1,Mask.rows / 8, 100, 30, 0, 0);

        for (size_t i = 0; i < circles.size(); i++) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            circle(frame, center, radius, Scalar(0, 255, 0), 2);
        }
        
        imshow("Detect", frame);
        imshow("hw", Mask);

        if (waitKey(1) == 27) {
            break;
        }
    }

    return 0;
}

void onTrackbar(int, void*){

}