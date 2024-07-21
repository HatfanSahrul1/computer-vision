#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include "opencv4/opencv2/calib3d.hpp"
#include "iostream"

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

double length=0.04;

int main(){
    cv::VideoCapture cap(0);

    cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    
    cv::Mat image, frame;
    cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) << 
    fx, 0, cx,
    0, fy, cy,
    0, 0, 1);
    cv::Mat distCoeffs = (cv::Mat_<double>(5,1) << k1, k2, p1, p2, k3);

    while(true){
        cap >> frame;

        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners;
        cv::aruco::ArucoDetector detector(dictionary, detectorParams);
        detector.detectMarkers(frame, markerCorners, markerIds);
        char ss[100];

        cv::Mat objPoints(4, 1, CV_32FC3);
        cv::Mat imagePoints(4, 1, CV_32FC3);
        std::vector<cv::Vec3d> rvec, tvec;

        objPoints.ptr<cv::Vec3f>(0)[0] = cv::Vec3f(248, 172, 0);
        objPoints.ptr<cv::Vec3f>(0)[1] = cv::Vec3f(175, 172, 0);
        objPoints.ptr<cv::Vec3f>(0)[2] = cv::Vec3f(175, 241, 0);
        objPoints.ptr<cv::Vec3f>(0)[3] = cv::Vec3f(248, 241, 0);
        
        cv::imshow("m", frame);

        if(!markerIds.empty()){
            for (size_t i = 0; i < markerIds.size(); ++i) {
                if(markerIds[i]==110){
                    std::cout<<"obj\timg\n"<<std::endl;
                    size_t numCorners = markerCorners[i].size();
                    for (size_t j = 0; j < numCorners; j++) {
                        imagePoints.ptr<cv::Vec2f>(i)[j] = cv::Vec2f(markerCorners[i][j].x, markerCorners[i][j].y);
                        std::cout<<objPoints.ptr<cv::Vec2f>(i)[j]<<" \t"<<imagePoints.ptr<cv::Vec2f>(i)[j]<<std::endl;

                    }
                }
            }
            if(imagePoints.size()==objPoints.size()){
                printf("ok\n");
                // cv::solvePnP(objPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec);
            }
            if (!rvec.empty() && !tvec.empty()) {
                std::cout << "rvec \n" 
                        << rvec[0][0] << "\n" 
                        << rvec[0][1] << "\n" 
                        << rvec[0][2] 
                        << "\ntvec\n" 
                        << tvec[0][0] << "\n" 
                        << tvec[0][1] << "\n" 
                        << tvec[0][2] << std::endl;
            } else {
                std::cout << "rvec or tvec is empty" << std::endl;
            }

        }

        if(cv::waitKey(30)==27){
            break;
        }
    }
    return 0;
}

