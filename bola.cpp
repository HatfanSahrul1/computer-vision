/*#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main() {
    // Baca gambar
    cv::Mat image = cv::imread("/home/hatfan/test2/bangun.jpg", cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Error: Unable to read the image." << std::endl;
        return -1;
    }

    // Ubah gambar ke dalam skala abu-abu
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Lakukan deteksi tepi dengan metode Canny
    cv::Mat edges;
    cv::Canny(gray, edges, 50, 150, 3);

    // Lakukan transformasi Hough Circle untuk mendeteksi lingkaran
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(edges, circles, cv::HOUGH_GRADIENT, 1, 50, 150, 30, 10, 50);

    if (!circles.empty()) {
        // Gambar lingkaran yang terdeteksi pada gambar asli
        for (size_t i = 0; i < circles.size(); ++i) {
            cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            cv::circle(image, center, radius, cv::Scalar(0, 255, 0), 2);
        }

        // Tampilkan gambar hasil deteksi
        cv::imshow("Deteksi Bola", image);
        cv::waitKey(0);
        cv::destroyAllWindows();
    } else {
        std::cout << "Tidak ada bola yang terdeteksi." << std::endl;
    }

    return 0;
}
*/

/*
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

int main() {
    // Load model and configuration files
    std::string modelConfig = "path/to/yolo.cfg";
    std::string modelWeights = "path/to/yolo.weights";
    cv::dnn::Net net = cv::dnn::readNetFromDarknet(modelConfig, modelWeights);
    
    if (net.empty()) {
        std::cerr << "Error: Unable to load YOLO model." << std::endl;
        return -1;
    }

    // Load image
    cv::Mat image = cv::imread("/home/hatfan/test2/bangun.jpg", cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Error: Unable to read the image." << std::endl;
        return -1;
    }

    // Convert image to blob
    cv::Mat blob = cv::dnn::blobFromImage(image, 1/255.0, cv::Size(416, 416), cv::Scalar(0,0,0), true, false);

    // Set the input blob
    net.setInput(blob);

    // Get output layer names
    std::vector<std::string> layerNames = net.getUnconnectedOutLayersNames();

    // Forward pass
    std::vector<cv::Mat> detections;
    net.forward(detections, layerNames);

    // Loop over the detections and draw bounding boxes
    for (const auto& detection : detections) {
        for (int i = 0; i < detection.rows; ++i) {
            cv::Mat detectionRow = detection.row(i);
            cv::Mat scores = detectionRow.colRange(5, detectionRow.cols);
            cv::Point classIdPoint;
            int maxClassId;
            double maxScore;
            cv::minMaxLoc(scores, nullptr, &maxScore, nullptr, &classIdPoint);
            maxClassId = classIdPoint.x;

            if (maxScore > 0.5) {
                // Get bounding box coordinates
                int centerX = static_cast<int>(detectionRow[0] * image.cols);
                int centerY = static_cast<int>(detectionRow[1] * image.rows);
                int width = static_cast<int>(detectionRow[2] * image.cols);
                int height = static_cast<int>(detectionRow[3] * image.rows);

                // Calculate bounding box coordinates
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                // Draw bounding box
                cv::rectangle(image, cv::Rect(left, top, width, height), cv::Scalar(0, 255, 0), 2);
            }
        }
    }

    // Display the result
    cv::imshow("YOLO Detection", image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
*/

#include <opencv2/opencv.hpp>

int main() {
    // Open camera
    cv::VideoCapture cap(0);  // 0 corresponds to the default camera (change it if you have multiple cameras)

    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open camera." << std::endl;
        return -1;
    }

    // Main loop for real-time processing
    while (true) {
        // Capture frame from camera
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Error: Unable to capture frame." << std::endl;
            break;
        }

        // Convert frame to grayscale
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Perform edge detection with the Canny method
        cv::Mat edges;
        cv::Canny(gray, edges, 50, 150, 3);

        // Perform Hough Circle Transform to detect circles
        std::vector<cv::Vec3f> circles;
        cv::HoughCircles(edges, circles, cv::HOUGH_GRADIENT, 1, 50, 150, 30, 10, 50);

        // Draw detected circles on the original frame
        if (!circles.empty()) {
            for (size_t i = 0; i < circles.size(); ++i) {
                cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                int radius = cvRound(circles[i][2]);
                cv::circle(frame, center, radius, cv::Scalar(0, 255, 0), 2);
            }

            // Display the frame with detected circles
            cv::imshow("Deteksi Bola", frame);
        } else {
            std::cout << "Tidak ada bola yang terdeteksi." << std::endl;
        }

        // Display the original frame with edges
        cv::imshow("Object Detection", edges);

        // Exit the loop if the 'ESC' key is pressed
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    // Release the camera and close all OpenCV windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}

