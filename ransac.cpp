#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

int main() {
    cv::VideoCapture cap(2);
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open the video capture device." << std::endl;
        return -1;
    }

    cv::namedWindow("Vertical Line Detection with RANSAC", cv::WINDOW_AUTOSIZE);
    
    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Error: Unable to capture frame." << std::endl;
            break;
        }

        cv::Mat grayImage;
        cv::cvtColor(frame, grayImage, cv::COLOR_BGR2GRAY);

        cv::Mat morphImage;
        cv::morphologyEx(grayImage, morphImage, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
        cv::GaussianBlur(morphImage, morphImage, cv::Size(5, 5), 0);

        cv::Mat mask;
        cv::inRange(morphImage, cv::Scalar(200), cv::Scalar(255), mask);

        int erodeSize = 1;
        int dilateSize = 1;
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * erodeSize + 1, 2 * erodeSize + 1), cv::Point(erodeSize, erodeSize));
        cv::erode(mask, mask, element);
        cv::dilate(mask, mask, element);

        cv::Mat edges;
        cv::Canny(mask, edges, 50, 150);

        std::vector<cv::Vec2f> lines;
        cv::HoughLines(edges, lines, 1, CV_PI / 180, 100);

        const int numIterations = 1000;
        const double distanceThreshold = 2.0;

        for (int iteration = 0; iteration < numIterations; ++iteration) {
            int index1 = cv::theRNG().uniform(0, lines.size());
            int index2 = cv::theRNG().uniform(0, lines.size());
            if (index1 == index2)
                continue;  // Avoid picking the same index

            cv::Point2f point1(lines[index1][0], lines[index1][1]);
            cv::Point2f point2(lines[index2][0], lines[index2][1]);

            float m = (point2.y - point1.y) / (point2.x - point1.x);
            float b = point1.y - m * point1.x;

            int inliers = 0;
            for (const auto& line : lines) {
                float x = line[0];
                float y = line[1];
                float distance = std::fabs(y - (m * x + b));
                if (distance < distanceThreshold) {
                    inliers++;
                }
            }

            if (inliers > 0) {
                std::cout << "Iteration " << iteration << ": " << inliers << " inliers" << std::endl;
            }
        }

        cv::Mat resultImage(frame.size(), frame.type(), cv::Scalar(0, 0, 0));
        for (const auto& line : lines) {
            float rho = line[0];
            float theta = line[1];
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
        cv::Mat combine(frame.size(), frame.type(), cv::Scalar(0, 0, 0));
        cv::bitwise_and(resultImage,edges, combine);

        cv::imshow("Vertical Line Detection with RANSAC", frame);
        cv::imshow("f",mask);

        char key = cv::waitKey(30);
        if (key == 27)  // ESC key to exit
            break;
    }

    return 0;
}
