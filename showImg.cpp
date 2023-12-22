#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img_gray=cv::imread("/home/hatfan/test2/test.jpg",1);
    cv::imshow("grayscale image",img_gray);
    cv::waitKey(0);
    cv::imwrite("colour.jpg",img_gray);
    return 0;
}
