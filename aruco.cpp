#include "opencv2/opencv.hpp"
#include <opencv2/aruco.hpp>
#include "opencv2/highui.hpp"
#include "opencv2/imgproc.hpp"

int main(){
    cv::Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefiedDictionary(cv::aruco::DICT_6X6_100);
    cv::aruco::drawMarker(dict,100,200,img,1);
    cv::namedWindow("out",0);
    cv::imshow("out",img);
    cv::waitKey(0);
}