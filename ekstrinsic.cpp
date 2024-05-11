#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include "opencv4/opencv2/calib3d.hpp"
#include "iostream"
#include "yaml-cpp/yaml.h"
double fx = 1000.0; // Focal length in x direction
double fy = 1000.0; // Focal length in y direction
double cx = 320.0;  // Principal point (optical center) x coordinate
double cy = 240.0;  // Principal point (optical center) y coordinate

// Example distortion coefficients
double k1 = 0.1; // Radial distortion coefficient 1
double k2 = 0.01; // Radial distortion coefficient 2
double p1 = 0.0; // Tangential distortion coefficient 1
double p2 = 0.0; // Tangential distortion coefficient 2
double k3 = 0.001;// Radial distortion coefficient 3

double length = 0;
int main() {

    cv::VideoCapture cap(2); // Use the default camera (you may need to adjust the camera index)

    if (!cap.isOpened()) {
        std::cerr << "Error: Failed to open camera!" << std::endl;
        cap.open(0);
    }

    cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

    cv::Mat image, frame;
    cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) <<
        fx, 0, cx,
        0, fy, cy,
        0, 0, 1);
    cv::Mat distCoeffs = (cv::Mat_<double>(5, 1) <<
        k1, k2, p1, p2, k3);

    while (true) {
        cap >> frame;

        YAML::Node config = YAML::LoadFile("/home/eros/test2/length.yaml");
        length = config["length"].as<double>();

        if (frame.empty()) {
            std::cerr << "Error: Failed to capture frame from camera!" << std::endl;
            break;
        }

        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners;
        cv::aruco::ArucoDetector detector(dictionary, detectorParams);
        detector.detectMarkers(frame, markerCorners, markerIds);
        char ss[100];

        if (!markerIds.empty()) {

            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(markerCorners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);

            for (size_t i = 0; i < markerIds.size(); ++i) {
                // Print marker ID
                std::cout << "Marker ID: " << markerIds[i] << std::endl;

                // Print rotation vector (rvec)
                std::cout << "Rotation vector (rvec): " << rvecs[i] << std::endl;

                // Print translation vector (tvec)
                std::cout << "Translation vector (tvec): " << tvecs[i] << std::endl;

                // Draw marker ID
                cv::putText(frame, std::to_string(markerIds[i]), markerCorners[i][0], cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);

                size_t numCorners = markerCorners[i].size();
                for (size_t j = 0; j < numCorners; j++) {
                    cv::Point2f corner = markerCorners[i][j];
                    std::sprintf(ss, "%.2f , %.2f", corner.x, corner.y );

                    // Mark the corners
                    cv::putText(frame, std::to_string(j + 1), corner, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
                    cv::circle(frame, corner, 2, cv::Scalar(0, 0, 255), 2);
                }
            }
        }

        cv::imshow("M", frame);

        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
