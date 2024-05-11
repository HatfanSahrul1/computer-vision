#include "opencv2/opencv.hpp"
#include "opencv4/opencv2/aruco.hpp"
#include "opencv4/opencv2/calib3d.hpp"
#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/core/utility.hpp"

#include "fstream"
#include "iostream"
#include "sstream"


int main(int argv, char** argc){
    cv::Mat cameraMatrix = cv::Mat::eye(3,3,CV_64F);
    cv::Mat distCoeffs = cv::Mat::zeros(8, 1, CV_64F);

    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);

    cv::aruco::DetectorParameters detectorParams;
    detectorParams.adaptiveThreshWinSizeMin=3;
    detectorParams.adaptiveThreshWinSizeMax=23;
    detectorParams.adaptiveThreshConstant=7;
    detectorParams.minMarkerPerimeterRate=0;
    detectorParams.maxMarkerPerimeterRate=1000;
    detectorParams.minMarkerDistanceRate=0;

    cv::VideoCapture cap(0);
    while (true) {
    cv::Mat frame;
    // Capture frame from video or read image
    if (!cap.isOpened()) {
        std::cerr << "Error opening video capture\n";
        return -1;
    }
    cap >> frame;
    // if (!image.data) {
    //     std::cerr << "Error loading image\n";
    //     return -1;
    // }

    // Grayscale conversion (optional, may improve detection)
    cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

    // Detect Aruco markers
    std::vector<std::vector<cv::Point2f>> corners;
    std::vector<int> ids;
    cv::aruco::detectMarkers(frame, dictionary, corners, ids, detectorParams);

    // Draw detected markers (optional)
    cv::aruco::drawDetectedMarkers(frame, corners, ids);

    // Camera pose estimation (if camera calibration parameters are available)
    if (!cameraMatrix.empty() && !distCoeffs.empty()) {
        std::vector<cv::Vec3d> rvecs, tvecs;
        // Assuming object points
    }
    }
}