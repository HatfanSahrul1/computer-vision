#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/aruco.hpp>

int main(){
     cv::VideoCapture inputVideo;
    
    // Try opening capture device with index 2
    inputVideo.open(2);
    if (!inputVideo.isOpened()) {
        std::cout << "Failed to open capture device with index 2. Trying default device (index 0)..." << std::endl;
        // Fall back to opening default capture device with index 0
        inputVideo.open(0);
    }

    // Check if capture device opened successfully
    if (!inputVideo.isOpened()) {
        std::cerr << "Error: Failed to open capture device!" << std::endl;
        return -1;
    }
    
    cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    cv::aruco::ArucoDetector detector(dictionary, detectorParams);

    while (inputVideo.grab()) {
        cv::Mat image, imageCopy;
        inputVideo.retrieve(image);
        image.copyTo(imageCopy);
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners, rejected;
        detector.detectMarkers(image, corners, ids, rejected);
        // if at least one marker detected
        if (ids.size() > 0)
            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
        cv::imshow("out", imageCopy);
        char key = (char) cv::waitKey(30);
        if (key == 27)
            break;
    }

    return 0;
}
