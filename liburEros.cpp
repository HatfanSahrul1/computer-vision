#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Open the default camera (camera index 0)
    VideoCapture cap(0);

    if (!cap.isOpened()) {
        cout << "Error opening the camera." << endl;
        return -1;
    }

    while (true) {
        // Capture a frame from the camera
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            cout << "End of video stream" << endl;
            break;
        }

        // Convert the frame to HSV color space
        Mat hsvFrame;
        cvtColor(frame, hsvFrame, COLOR_BGR2HSV);

        // Define the range of orange color in HSV
        Scalar lowerOrange = Scalar(0, 100, 100);
        Scalar upperOrange = Scalar(20, 255, 255);

        // Threshold the frame to extract orange color
        Mat orangeMask;
        inRange(hsvFrame, lowerOrange, upperOrange, orangeMask);

        // Apply GaussianBlur to reduce noise and improve circle detection
        GaussianBlur(orangeMask, orangeMask, Size(9, 9), 2, 2);

        // Use the Hough Circle Transform to detect circles
        vector<Vec3f> circles;
        HoughCircles(orangeMask, circles, HOUGH_GRADIENT, 1, orangeMask.rows / 8, 100, 30, 0, 0);

        // Draw the circles on the original frame
        for (size_t i = 0; i < circles.size(); i++) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            circle(frame, center, radius, Scalar(0, 255, 0), 2); // Green circle
        }

        // Display the result
        imshow("Orange Ball Detection", frame);

        // Break the loop if the user presses the 'Esc' key
        if (waitKey(1) == 27) {
            break;
        }
    }

    return 0;
}
