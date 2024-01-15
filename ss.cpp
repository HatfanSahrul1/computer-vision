#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**) {
    cv::VideoCapture vcap;
    cv::Mat frame;

    const std::string videoStreamAddress = "https://10.252.133.72:8080/videofeed?something.mjpeg";

    // Open the video stream and make sure it's opened
    if (!vcap.open(videoStreamAddress)) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }

    // Set the desired window size (fullscreen)
    cv::namedWindow("Output Window", cv::WINDOW_NORMAL);
    //cv::setWindowProperty("Output Window", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    int a=0;
    //string f="/home/hatfan/test2/gbr/chessboard_"+a+".jpg";
    for (;;) {
        vcap.read(frame);

        // Display the frame
        cv::imshow("Output Window", frame);
        if(cv::waitKey(30)==115){
            std::stringstream filename;
            filename << "/home/hatfan/test2/gbr/chessboard_" << a << ".jpg";

            // Save the frame
            cv::imwrite(filename.str(), frame);

            // Increment the counter
            a++;

            cout<<"ss"<<endl;
        }


        if (cv::waitKey(30) == 27) // Exit when the 'Esc' key is pressed
            break;
    }

    return 0;
}
