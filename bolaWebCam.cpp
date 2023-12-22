#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**) {
    cv::VideoCapture vcap;
    cv::Mat frame;
    
    //buka kamera
    const std::string videoStreamAddress = "https://10.252.131.184:8080/videofeed?something.mjpeg";

    if (!vcap.open(videoStreamAddress)) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }

    // set size 
    const int windowWidth = 640;  // Set your desired width
    const int windowHeight = windowWidth * 9 / 16; // Maintain the 16:9 aspect ratio

    // buat window
    cv::namedWindow("Deteksi Bola", cv::WINDOW_NORMAL);

    // resize
    cv::resizeWindow("Deteksi Bola", windowWidth, windowHeight);

    for (;;) {
        vcap.read(frame);

        // kode grayscale
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // blur gambar
        cv::GaussianBlur(gray, gray, cv::Size(9, 9), 2, 2);

        // Hough Circle detection
        std::vector<cv::Vec3f> circles;
        cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 8, 100, 30, 10, 50);

        // lingkaran hijau pada bola
        for (const auto& circle : circles) {
            cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
            int radius = cvRound(circle[2]);
            cv::circle(frame, center, radius, cv::Scalar(0, 255, 0), 2);
        }

        // menghitung bola yg terdeteksi
        string text = "Bola terdeteksi: " + to_string(circles.size());
        cv::putText(frame, text, Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);

        // Display 
        cv::imshow("Deteksi Bola", frame);

        //musik
        /*if (circles.size() >= 1) {
           if(!isNot) system("canberra-gtk-play -f /home/hatfan/test2/mix.wav");
            cv::waitKey(1);
        }*/

        //"esc" untuk keluar atau cancel (ctrl+c) dari terminal
        if (cv::waitKey(1) == 27) 
            break;
    }

    return 0;
}
