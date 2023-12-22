#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Open the default camera (camera index 0)
    cv::VideoCapture cap(0);

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    // Create a window to display the camera feed
    cv::namedWindow("Camera Feed", cv::WINDOW_NORMAL);

    while (true) {
        cv::Mat frame;

        // Capture a frame from the camera
        cap >> frame;

        // Check if the frame was successfully captured
        if (frame.empty()) {
            std::cerr << "Error: Could not capture frame." << std::endl;
            break;
        }

        // Display the frame
        cv::imshow("Camera Feed", frame);

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
