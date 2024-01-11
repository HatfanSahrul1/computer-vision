#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    VideoCapture cap(0);

    Mat frame;
    const string videoStreamAddress = "https://10.252.133.72:8080/videofeed?something.mjpeg";
    cap.open(videoStreamAddress);
    /*if (!cap.isOpened()) {
        cout << "Error opening the camera." << endl;
        return -1;
    }*/

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Green and White Only", WINDOW_AUTOSIZE);

    while (true) {
        cap >> frame;

        if (frame.empty()) {
            break;
        }

        // Apply Gaussian Blur to reduce noise
        GaussianBlur(frame, frame, Size(5, 5), 2, 2);

        // Convert the frame from BGR to HSV color space
        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // Define the ranges for green and white in HSV
        Scalar lowerGreen = Scalar(40, 40, 40);  // Example values, you may need to adjust
        Scalar upperGreen = Scalar(80, 255, 255);

        Scalar lowerWhite = Scalar(0, 0, 200);
        Scalar upperWhite = Scalar(255, 30, 255);

        // Create binary masks for green and white
        Mat greenMask, whiteMask;
        inRange(hsv, lowerGreen, upperGreen, greenMask);
        inRange(hsv, lowerWhite, upperWhite, whiteMask);

        // Combine the masks
        Mat combinedMask = greenMask | whiteMask;

        // Apply the combined mask to the original frame
        Mat result;
        bitwise_and(frame, frame, result, combinedMask);

        imshow("Original", frame);
        imshow("Green and White Only", result);

        char key = waitKey(30);
        if (key == 27) // Press 'Esc' to exit the loop
            break;
    }

    return 0;
}
