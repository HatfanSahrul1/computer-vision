#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

void onTrackbar(int, void*){}
//green
int GL_H=40,GL_S=40,GL_V=40;
int GH_H=80,GH_S=255,GH_V=255;

//white
int WL_H=0,WL_S=0,WL_V=200;
int WH_H=255,WH_S=30,WH_V=255;

//orange
int OL_H=0,OL_S=100,OL_V=100;
int OH_H=20,OH_S=255,OH_V=255;

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
    namedWindow("filter", WINDOW_AUTOSIZE);
    /*namedWindow("white", WINDOW_AUTOSIZE);
    namedWindow("green", WINDOW_AUTOSIZE);
    namedWindow("orange", WINDOW_AUTOSIZE);*/

    /*//green
    createTrackbar("gLow_H","green",&GL_H,255,onTrackbar);
    createTrackbar("gHigh_H","green",&GH_H,255,onTrackbar);
    createTrackbar("gLow_S","green",&GL_S,255,onTrackbar);
    createTrackbar("gHigh_S","green",&GH_S,255,onTrackbar);
    createTrackbar("gLow_V","green",&GL_V,255,onTrackbar);
    createTrackbar("gHigh_V","green",&GH_V,255,onTrackbar);

    //white
    createTrackbar("wLow_H","white",&WL_H,255,onTrackbar);
    createTrackbar("wHigh_H","white",&WH_H,255,onTrackbar);
    createTrackbar("wLow_S","white",&WL_S,255,onTrackbar);
    createTrackbar("wHigh_S","white",&WH_S,255,onTrackbar);
    createTrackbar("wLow_V","white",&WL_V,255,onTrackbar);
    createTrackbar("wHigh_V","white",&WH_V,255,onTrackbar);

    //orange
    createTrackbar("oLow_H","orange",&OL_H,255,onTrackbar);
    createTrackbar("oHigh_H","orange",&OH_H,255,onTrackbar);
    createTrackbar("oLow_S","orange",&OL_S,255,onTrackbar);
    createTrackbar("oHigh_S","orange",&OH_S,255,onTrackbar);
    createTrackbar("oLow_V","orange",&OL_V,255,onTrackbar);
    createTrackbar("oHigh_V","orange",&OH_V,255,onTrackbar);
    */
    while (true) {
        cap >> frame;

        if (frame.empty()) {
            break;
        }
        GaussianBlur(frame, frame, Size(5, 5), 2, 2);

        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        Scalar lowerGreen = Scalar(GL_H, GL_S, GL_V);
        Scalar upperGreen = Scalar(GH_H,GH_S,GH_V);

        Scalar lowerWhite = Scalar(WL_H,WL_S,WL_V);
        Scalar upperWhite = Scalar(WH_H,WH_S,WH_V);

        Scalar lowerOren = Scalar(OL_H,OL_S,OL_V);
        Scalar upperOren = Scalar(OH_H,OH_S,OH_V);

        Mat greenMask, whiteMask, orenMask;
        inRange(hsv, lowerGreen, upperGreen, greenMask);
        inRange(hsv, lowerWhite, upperWhite, whiteMask);
        inRange(hsv, lowerOren,upperOren,orenMask);

        std::vector<cv::Vec3f> circles;
        cv::HoughCircles(orenMask, circles, cv::HOUGH_GRADIENT, 1, orenMask.rows / 8, 100, 30, 10, 50);

        // lingkaran hijau pada bola
        for (const auto& circle : circles) {
            cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
            int radius = cvRound(circle[2]);
            cv::circle(frame, center, radius, cv::Scalar(0, 255, 0), 2);
        }

        Mat combinedMask =greenMask | whiteMask | orenMask;

        Mat result;
        bitwise_or(frame, frame, result, orenMask);
        cv::Vec3b oren(0, 100, 255);
        result.setTo(oren, result);

        bitwise_or(frame,result,result,whiteMask);

        
        // Set the purple color in the regions corresponding to the combined mask
        

        imshow("Original", frame);
        imshow("filter", result);
        

        char key = waitKey(30);
        if (key == 27) // Press 'Esc' to exit the loop
            break;
    }

    return 0;
}