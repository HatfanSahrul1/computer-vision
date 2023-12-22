#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    VideoCapture cap;
    Mat frame;

    string videoStreamAddress="https://10.252.131.184:8080/videofeed?something.mjpeg";
    if (!cap.open(videoStreamAddress)) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }

    Scalar lowOren=Scalar(5,100,100);
    Scalar highOren=Scalar(15,255,255);    

    namedWindow("Tugas Deteksi Bola",WINDOW_AUTOSIZE);
    namedWindow("bw",WINDOW_AUTOSIZE);

    Mat gambar=imread("/home/hatfan/test2/bolaBanyak.png",1);
    waitKey(1);
    //imshow("bola oren",gambar);

    for(;;){
        cap.read(frame);

        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        Mat mask;
        inRange(hsv,lowOren,highOren,mask);

        resize(mask, mask, Size(900, (900.0 / mask.cols) * mask.rows));
        imshow("bw", mask);

        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
        morphologyEx(mask, mask, MORPH_OPEN, kernel);
        morphologyEx(mask, mask, MORPH_CLOSE, kernel);

        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (const auto& contour : contours) {
            double area = contourArea(contour);

            // Adjust the area threshold based on your specific case
            if (area > 100) {
                // Draw a bounding box around the detected orange ball
                Rect boundingBox = boundingRect(contour);
                rectangle(frame, boundingBox, Scalar(0, 255, 0), 2);
            }
        }
        resize(frame, frame, Size(900, (900.0 / frame.cols) * frame.rows));
        imshow("Tugas Deteksi Bola", frame);

        if(waitKey(1)==27)break;
    }

    cap.release();
    destroyAllWindows();
}