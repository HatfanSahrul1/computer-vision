#include <opencv2/opencv.hpp>

int main() {
    cv::Mat image(300, 300, CV_8UC3, cv::Scalar(255, 0, 0));
    cv::imshow("OpenCV Example", image);
    cv::waitKey(0);
    return 0;
}
