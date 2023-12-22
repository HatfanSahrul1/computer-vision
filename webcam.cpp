#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**) {
    cv::VideoCapture vcap;
    cv::Mat frame;

    const std::string videoStreamAddress = "https://192.168.1.5:8080/videofeed?something.mjpeg";

    // Open the video stream and make sure it's opened
    if (!vcap.open(videoStreamAddress)) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }

    // Load pre-trained face detector
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(cv::samples::findFile("haarcascades/haarcascade_frontalface_alt.xml"))) {
        std::cerr << "Error loading face cascade." << std::endl;
        return -1;
    }

    // Set the desired window size (16:9 portrait)
    const int windowHeight = 720; // 720p resolution
    const int windowWidth = windowHeight * 9 / 16;

    // Create a named window
    cv::namedWindow("Output Window", cv::WINDOW_NORMAL);

    // Resize the window
    cv::resizeWindow("Output Window", windowWidth, windowHeight);

    for (;;) {
        vcap.read(frame);

        // Convert the frame to grayscale for face detection
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detect faces in the frame
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 4);

        // Draw rectangles around the detected faces
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        // Display the number of faces detected
        string text = "Faces detected: " + to_string(faces.size());
        cv::putText(frame, text, Point(10, 50), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 0), 2);

        // Display the frame
        cv::imshow("Output Window", frame);

        // Play a sound when more than two faces are detected
        if (faces.size() >= 2) {
            system("canberra-gtk-play -f /home/hatfan/test2/mix.wav");
            cv::waitKey(1);
        }

        if (cv::waitKey(1) == 27) // Exit when the 'Esc' key is pressed
            break;
    }

    return 0;
}