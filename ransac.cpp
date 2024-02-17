#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

int main() {
    // Video capture from default camera (you can change the argument to your camera index or video file)
    cv::VideoCapture cap(2);
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open the video capture device." << std::endl;
        return -1;
    }

    cv::namedWindow("Vertical Line Detection with RANSAC", cv::WINDOW_AUTOSIZE);

    while (true) {
        cv::Mat frame;
        cap >> frame; // Capture frame from the video

        if (frame.empty()) {
            std::cerr << "Error: Unable to capture frame." << std::endl;
            break;
        }

        // Convert the frame to grayscale
        cv::Mat grayImage;
        cv::cvtColor(frame, grayImage, cv::COLOR_BGR2GRAY);

        // Apply morphology operations (e.g., closing) to enhance features
        cv::Mat morphImage;
        // Apply GaussianBlur to reduce noise
        cv::morphologyEx(grayImage, morphImage, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
        cv::GaussianBlur(morphImage, morphImage, cv::Size(5, 5), 0);

        cv::Mat mask;
        cv::inRange(morphImage, cv::Scalar(200), cv::Scalar(255), mask);

        int erodeSize = 1;
        int dilateSize = 1;
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * erodeSize + 1, 2 * erodeSize + 1), cv::Point(erodeSize, erodeSize));
        cv::erode(mask, mask, element);
        cv::dilate(mask, mask, element);

        // Use Canny edge detector to find edges in the image
        cv::Mat edges;
        cv::Canny(mask, edges, 50, 150);

        // Find lines using Hough transform
        std::vector<cv::Vec2f> lines;
        cv::HoughLines(edges, lines, 1, CV_PI / 180, 100);

        // RANSAC parameters
        const int numIterations = 1000;  // Number of RANSAC iterations
        const double distanceThreshold = 2.0;  // Maximum distance to consider a point as an inlier

        // RANSAC loop
        for (int iteration = 0; iteration < numIterations; ++iteration) {
            // Randomly select two points
            int index1 = cv::theRNG().uniform(0, lines.size());
            int index2 = cv::theRNG().uniform(0, lines.size());
            cv::Point2f point1(lines[index1][0], lines[index1][1]);
            cv::Point2f point2(lines[index2][0], lines[index2][1]);

            // Compute the line model (y = mx + b)
            float m = (point2.y - point1.y) / (point2.x - point1.x);
            float b = point1.y - m * point1.x;

            // Count inliers
            int inliers = 0;
            for (const auto& line : lines) {
                float x = line[0];
                float y = line[1];
                float distance = std::fabs(y - (m * x + b));
                if (distance < distanceThreshold) {
                    inliers++;
                }
            }

            // Update the best model if this iteration has more inliers
            if (inliers > 0) {
                std::cout << "Iteration " << iteration << ": " << inliers << " inliers" << std::endl;
            }
        }

        // Draw only vertical lines
        for (const auto& line : lines) {
            float rho = line[0];
            float theta = line[1];
            // Filter lines based on their orientation (vertical)
            if (std::fabs(theta) < CV_PI / 4.0 || std::fabs(theta - CV_PI) < CV_PI / 4.0) {
                double a = std::cos(theta);
                double b = std::sin(theta);
                double x0 = a * rho;
                double y0 = b * rho;
                cv::Point pt1(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
                cv::Point pt2(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));
                cv::line(frame, pt1, pt2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
            }
        }

        // Display the result
        cv::imshow("Vertical Line Detection with RANSAC", frame);

        char key = cv::waitKey(30);
        if (key == 27)  // ESC key to exit
            break;
    }

    return 0;
}
