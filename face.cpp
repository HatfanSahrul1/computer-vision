#include <opencv2/opencv.hpp>

int main() {
    // Load the pre-trained Haar Cascade face detection model
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade. Exiting..." << std::endl;
        return -1;
    }

    // Open a video capture object (you can replace '0' with the camera index if using a webcam)
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video capture. Exiting..." << std::endl;
        return -1;
    }

    // Create a window to display the output
    cv::namedWindow("Face Detection", cv::WINDOW_AUTOSIZE);

    while (true) {
        // Capture a frame from the video source
        cv::Mat frame;
        cap >> frame;

        // Convert the frame to grayscale for face detection
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Perform face detection
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 4);

        // Draw rectangles around detected faces
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        // Display the frame with face rectangles
        cv::imshow("Face Detection", frame);

        // Break the loop if 'ESC' key is pressed
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    // Release the video capture object
    cap.release();

    // Close all OpenCV windows
    cv::destroyAllWindows();

    return 0;
}
