#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat frame = imread("/home/hatfan/test2/bolaBanyak.png");
    
    if (frame.empty()) {
        cerr << "Error: Couldn't open the image." << endl;
        return -1;
    }

    Scalar lowerOrange = Scalar(0, 100, 100);
    Scalar upperOrange = Scalar(20, 255, 255);

    namedWindow("Ball Detection", WINDOW_NORMAL);
    namedWindow("bw", WINDOW_GUI_EXPANDED);

    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);

    Mat mask;
    inRange(hsv, lowerOrange, upperOrange, mask);

    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (const auto &contour : contours) {
        double area = contourArea(contour);

        if (area > 100) {
            Point2f center;
            float radius;
            minEnclosingCircle(contour, center, radius);

            circle(frame, center, static_cast<int>(radius), Scalar(0, 255, 0), 2);
        }
    }

    imshow("Ball Detection", frame);
    imshow("bw", mask);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
