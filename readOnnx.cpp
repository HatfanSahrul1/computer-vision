#include <opencv2/opencv.hpp>
#include <opencv2/dnn/dnn.hpp>

#define PROJECT_PATH "/home/hatfan/test2"

int main() {
    // Load the ONNX model
    cv::dnn::Net net = cv::dnn::readNetFromONNX(PROJECT_PATH + "/models/L-normal.onnx");

    // Read input image
    cv::Mat inputImage = cv::imread(PROJECT_PATH + "/L.jpeg");

    if (inputImage.empty()) {
        std::cerr << "Error: Could not read the input image." << std::endl;
        return -1;
    }

    // Preprocess the input image
    cv::Mat blob = cv::dnn::blobFromImage(inputImage, 1.0, cv::Size(300, 300), cv::Scalar(127.5, 127.5, 127.5), true, false);

    // Set input
    net.setInput(blob);

    // Run forward pass
    cv::Mat detection = net.forward();

    // Post-process the results
    // (This depends on the structure of your ONNX model and the format of its output)

    // Display the input image
    cv::imshow("Input Image", inputImage);

    // Display or save the results
    // (e.g., draw bounding boxes on the input image)

    // ...

    // Wait for a key press
    cv::waitKey(0);

    return 0;
}
