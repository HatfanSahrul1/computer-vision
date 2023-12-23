#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    VideoCapture cap(0);
    Mat frame;

    string videoStreamAddress = "https://10.252.131.184:8080/videofeed?something.mjpeg";
    if (!cap.open(videoStreamAddress)) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }

    Scalar lowOren = Scalar(5, 100, 100);
    Scalar highOren = Scalar(15, 255, 255);

    namedWindow("Tugas Deteksi Bola", WINDOW_AUTOSIZE);
    namedWindow("bw", WINDOW_AUTOSIZE);

    Mat gambar = imread("/home/hatfan/test2/bolaBanyak.png", 1);
    waitKey(1);
    imshow("bola oren", gambar);

    // Trackbars for tuning Hough Circle parameters
    int cannyThreshold = 100;
    int accumulatorThreshold = 50;

    createTrackbar("Canny threshold", "Tugas Deteksi Bola", &cannyThreshold, 255);
    createTrackbar("Accumulator Threshold", "Tugas Deteksi Bola", &accumulatorThreshold, 200);

    for (;;) {
        cap.read(frame);

        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        Mat mask;
        inRange(hsv, lowOren, highOren, mask);

        GaussianBlur(mask, mask, Size(5, 5), 0);

        resize(mask, mask, Size(900, (900.0 / mask.cols) * mask.rows));
        imshow("bw", mask);

        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (const auto &contour : contours) {
            double area = contourArea(contour);

            if (area > 100) {
                // Use Hough Circle detection on the binary mask
                vector<Vec3f> circles;
                HoughCircles(mask, circles, HOUGH_GRADIENT, 1, mask.rows / 8, cannyThreshold, accumulatorThreshold, 0, 0);

                // Draw the circles on the original frame
                for (const auto &circle : circles) {
                    Point center(cvRound(circle[0]), cvRound(circle[1]));
                    int radius = cvRound(circle[2]);
                    circle(frame, center, radius, Scalar(0, 255, 0), 2);
                }
            }
        }
        resize(frame, frame, Size(900, (900.0 / frame.cols) * frame.rows));
        imshow("Tugas Deteksi Bola", frame);

        if (waitKey(1) == 27) break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
