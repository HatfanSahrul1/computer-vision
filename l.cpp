#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){

    cv::Mat gambar=imread("/home/hatfan/test2/lpng.jpeg");

std::vector<cv::Point2f> inputs;

inputs.push_back(cv::Point(74,114)); // manually defined landmark
inputs.push_back(cv::Point(130,114)); // manually defined landmark 

std::vector<cv::KeyPoint> kp;
for( size_t i = 0; i < inputs.size(); i++ ) {
kp.push_back(cv::KeyPoint(inputs[i], 1.f));
}

cv::Mat descriptors;
cv::SiftFeatureDetector detector;
detector.compute(gambar, kp, descriptors); // descriptors are the sift descriptors on manually defined landmarks::imshow("s",gambar);
}