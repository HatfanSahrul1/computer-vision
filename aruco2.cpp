#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

int main() {
    
    cv::VideoCapture cap(2); // Use the default camera (you may need to adjust the camera index)

    if (!cap.isOpened()) {
        std::cerr << "Error: Failed to open camera!" << std::endl;
        cap.open(0);
    }

    cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    
    cv::Mat image, frame;

    while (true) {
        cap >> frame;

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
            cv::aruco::drawDetectedMarkers(frame, markerCorners, markerIds);

            for (size_t i = 0; i < markerIds.size(); ++i) {
                cv::putText(frame, std::to_string(markerIds[i]), markerCorners[i][0], cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
                
                size_t numCorners = markerCorners[i].size();
                for (size_t j = 0; j < numCorners; j++) {
                    cv::Point2f corner = markerCorners[i][j];
                    std::sprintf(ss, "%.2f , %.2f", corner.x, corner.y );

                    // Mark the first corner with the value 1
                    if (j == 0) {
                        cv::putText(frame, "1", corner, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
                        std::cout<<"1 "<<markerCorners[i][j];
                    }else if (j == 1) {
                        cv::putText(frame, "2", corner, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
                        std::cout<<" 2 "<<markerCorners[i][j];
                    }else if (j == 2) {
                        cv::putText(frame, "3", corner, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
                        std::cout<<" 3 "<<markerCorners[i][j];
                    }
                    // Mark the last corner with the value 4
                    else if (j == numCorners - 1) {
                        cv::putText(frame, "4", corner, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
                        std::cout<<" 4 "<<markerCorners[i][j]<<std::endl;
                    }

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
