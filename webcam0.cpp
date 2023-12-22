#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**) {
    cv::VideoCapture vcap;
    cv::Mat frame;

    const std::string videoStreamAddress = "https://192.168.1.16:8080/videofeed?something.mjpeg";

    // Open the video stream and make sure it's opened
    if (!vcap.open(videoStreamAddress)) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }

    // Set the desired window size (fullscreen)
    cv::namedWindow("Output Window", cv::WINDOW_NORMAL);
    cv::setWindowProperty("Output Window", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    for (;;) {
        vcap.read(frame);

        // Display the frame
        cv::imshow("Output Window", frame);

        if (cv::waitKey(1) == 27) // Exit when the 'Esc' key is pressed
            break;
    }

    return 0;
}
