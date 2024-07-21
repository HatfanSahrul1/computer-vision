#include <opencv2/opencv.hpp>
#include <iostream>

int main(){
    cv::Mat rvec=(cv::Mat_<double>(3,1)<<0.2,0.1,0.3);

    cv::Mat rotation_matrik;
    std::cerr<<"rvec : \n"<<rvec<<"\n\nrotate mat : \n"<<rotation_matrik<<"\n==========="<<std::endl;

    cv::Rodrigues(rvec, rotation_matrik);

    cv::Mat inver=(cv::Mat_<double>(2,2)<<0.2,0.1,0.3,0.7);

    std::cerr<<"rvec : \n"<<rvec<<"\n\nrotate mat : \n"<<rotation_matrik<<"\n==========="<<std::endl;
    std::cerr<<"inver normal : \n"<<inver<<"\n\ninver inv: \n"<<inver.inv()<<std::endl;
    return 0;
}