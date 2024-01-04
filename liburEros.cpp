#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);

    if (!cap.isOpened()) {
        cout << "Error opening the camera." << endl;
        return -1;
    }

    while (true) {
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            cout << "End of video stream" << endl;
            break;
        }

        // Convert the frame to HSV color space
        Mat hsvFrame;
        cvtColor(frame, hsvFrame, COLOR_BGR2HSV);

        Scalar lowOrange = Scalar(0, 100, 100);
        Scalar upOrange = Scalar(20, 255, 255);

        Mat Mask;
        inRange(hsv, lowOrange, upOrange, Mask);

        GaussianBlur(Mask, Mask, Size(9, 9), 2, 2);

        vector<Vec3f> circles;
        HoughCircles(orangeMask, circles, HOUGH_GRADIENT, 1, orangeMask.rows / 8, 100, 30, 0, 0);

        for (size_t i = 0; i < circles.size(); i++) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            circle(frame, center, radius, Scalar(0, 255, 0), 2);
        }
        
        imshow("Orange Ball Detection", frame);
        imshow("hw", Mask);

        if (waitKey(1) == 27) {
            break;
        }
    }

    return 0;
}