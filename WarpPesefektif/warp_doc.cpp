#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

void warpPerspectiveDemo();

int main()
{
    warpPerspectiveDemo();
    return 0;
}

void warpPerspectiveDemo()
{
    cv::VideoCapture cap(0);  // 0 means the default camera
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open camera or video." << std::endl;
        return;
    }

    std::string windowTitle = "Perspective Transformation Demo";
    std::vector<cv::Point2f> roi_corners(4);
    std::vector<cv::Point2f> dst_corners(4);
    bool validation_needed = true;

    cv::namedWindow(windowTitle, cv::WINDOW_NORMAL);
    cv::namedWindow("Warped Image", cv::WINDOW_AUTOSIZE);
    cv::moveWindow("Warped Image", 20, 20);
    cv::moveWindow(windowTitle, 330, 20);

    bool endProgram = false;

    while (!endProgram) {
        cv::Mat frame;
        cap >> frame;  // Capture frame from video/camera

        if (frame.empty()) {
            std::cerr << "Error: Cannot capture frame from camera/video." << std::endl;
            break;
        }

        if (validation_needed) {
            float frame_width = static_cast<float>(frame.cols);
            float frame_height = static_cast<float>(frame.rows);

            // Automatically define trapezoid points in the middle of the frame
            roi_corners[0] = cv::Point2f(frame_width * 0.3f, frame_height * 0.3f);  // TL
            roi_corners[1] = cv::Point2f(frame_width * 0.7f, frame_height * 0.3f);  // TR
            roi_corners[2] = cv::Point2f(frame_width * 0.8f, frame_height * 0.7f);  // BR
            roi_corners[3] = cv::Point2f(frame_width * 0.2f, frame_height * 0.7f);  // BL

            validation_needed = false;
        }

        // Draw trapezoid on the frame
        for (int i = 0; i < 4; ++i) {
            cv::line(frame, roi_corners[i], roi_corners[(i + 1) % 4], cv::Scalar(0, 0, 255), 2);
            cv::circle(frame, roi_corners[i], 5, cv::Scalar(0, 255, 0), 3);
        }

        cv::imshow(windowTitle, frame);

        // Calculate the midpoints of the trapezoid
        std::vector<cv::Point2f> midpoints(4);
        midpoints[0] = (roi_corners[0] + roi_corners[1]) / 2;
        midpoints[1] = (roi_corners[1] + roi_corners[2]) / 2;
        midpoints[2] = (roi_corners[2] + roi_corners[3]) / 2;
        midpoints[3] = (roi_corners[3] + roi_corners[0]) / 2;

        // Define destination points for perspective transformation
        dst_corners[0] = cv::Point2f(0, 0);
        dst_corners[1] = cv::Point2f(static_cast<float>(cv::norm(midpoints[1] - midpoints[3])), 0);
        dst_corners[2] = cv::Point2f(dst_corners[1].x, static_cast<float>(cv::norm(midpoints[0] - midpoints[2])));
        dst_corners[3] = cv::Point2f(0, dst_corners[2].y);

        cv::Size warped_image_size = cv::Size(cvRound(dst_corners[2].x), cvRound(dst_corners[2].y));
        cv::Mat M = cv::getPerspectiveTransform(roi_corners, dst_corners);
        cv::Mat warped_image;
        cv::warpPerspective(frame, warped_image, M, warped_image_size);  // Perform perspective transformation
        cv::imshow("Warped Image", warped_image);

        char c = static_cast<char>(cv::waitKey(10));
        if ((c == 'q') || (c == 'Q') || (c == 27)) {
            endProgram = true;
        }
    }
}
