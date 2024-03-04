#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

int main() {
    // Define the 3D object points of the marker
    float markerLength = 100.0f;  // Adjust the marker length as needed
    cv::Mat objPoints(4, 3, CV_32FC1);
    objPoints.ptr<cv::Vec3f>(0)[0] = cv::Vec3f(-markerLength / 2.f, markerLength / 2.f, 0);
    objPoints.ptr<cv::Vec3f>(0)[1] = cv::Vec3f(markerLength / 2.f, markerLength / 2.f, 0);
    objPoints.ptr<cv::Vec3f>(0)[2] = cv::Vec3f(markerLength / 2.f, -markerLength / 2.f, 0);
    objPoints.ptr<cv::Vec3f>(0)[3] = cv::Vec3f(-markerLength / 2.f, -markerLength / 2.f, 0);

    // Define the ArUco dictionary and detector parameters
    cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

    // Convert the ArUco dictionary to an image
    cv::Mat dictionaryImage;
    cv::drawMarker(dictionary, 0, 200, dictionaryImage);

    // Create an ArUco marker image using the converted image
    int markerId = 23;  // Marker ID = 23
    int sidePixels = 200;
    cv::Mat markerImage;
    dictionaryImage.copyTo(markerImage);  // Copy the converted image
    cv::drawMarker(dictionary, markerId, sidePixels, markerImage);

    // Save the marker image (optional)
    cv::imwrite("marker23.png", markerImage);

    // Detect the marker in an image
    cv::Mat inputImage = cv::imread("/home/hatfan/test2/marker23.png");  // Replace with your image path
    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners;
    cv::aruco::detectMarkers(inputImage, dictionary, markerCorners, markerIds, detectorParams);

    // Draw the detected markers on the image
    cv::aruco::drawDetectedMarkers(inputImage, markerCorners, markerIds);

    // Display the image with markers
    cv::imshow("Detected Markers", inputImage);
    cv::waitKey(0);

    return 0;
}
