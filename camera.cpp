#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
#define WORK_PATH "/home/hatfan/fokusL/"

using namespace std;
using namespace cv;

int c=1355;
int main() {
    // Open the default camera (camera index 0)
    cv::VideoCapture cap(3);

    cin>>c;

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    // Create a window to display the camera feed
    cv::namedWindow("Camera Feed", cv::WINDOW_NORMAL);
    stringstream normal, Tmask, Tedge;

    while (true) {
        cv::Mat frame;

        // Capture a frame from the camera
        cap >> frame;
        GaussianBlur(frame,frame,Size(5,5),2,2);
        Mat hls, mask, edge;
        cvtColor(frame, hls, COLOR_BGR2HLS);
        mask=Mat::zeros(640, 480, CV_8UC3);

        Mat element = getStructuringElement(MORPH_RECT, Size(3,3));//, Point(morph_size, morph_size));
        morphologyEx(hls, hls, MORPH_CLOSE, element, Point(-1, -1), 2);


        inRange(hls, Scalar(0, 150, 0), Scalar(180, 255, 255), mask);

        erode(hls, hls, getStructuringElement(MORPH_ELLIPSE, Size(3,3)));
        dilate(hls, hls, getStructuringElement(MORPH_ELLIPSE, Size(3,3)));

        Canny(mask, edge, 0,0,3);

        // Check if the frame was successfully captured
        if (frame.empty()) {
            std::cerr << "Error: Could not capture frame." << std::endl;
            break;
        }

        // Display the frame
        cv::imshow("Camera Feed", frame);
        imshow("mask", mask);
        imshow("canny", edge);

        if(waitKey(30)=='x'){
            normal<<WORK_PATH<<"normal/cap_Normal_"<<c<<".jpg";
            Tedge<<WORK_PATH<<"canny/cap_canny_"<<c<<".jpg";
            Tmask<<WORK_PATH<<"mask/cap_mask_"<<c<<".jpg";
            imwrite(normal.str(), frame);
            imwrite(Tedge.str(),edge);
            imwrite(Tmask.str(),mask);
            cout<<normal.str()<<endl;
            normal.str("");
            Tedge.str("");
            Tmask.str("");
            c++;
        }

        // Break the loop if the 'ESC' key is pressed
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    // Release the VideoCapture and destroy the window when done
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
