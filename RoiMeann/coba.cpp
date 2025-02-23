#include <iostream>
#include <opencv2/opencv.hpp>

int Rx = 30, Ry =30, Rrow = 50, Rcol=50;
int main(){
    cv::Mat frame=cv::imread("/home/eros/cv/gawang.jpeg");
    
    cv::namedWindow("Roi_pos", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("x", "Roi_pos", &Rx, frame.cols-2);
    cv::createTrackbar("y", "Roi_pos", &Ry, frame.rows-2);
    cv::createTrackbar("row", "Roi_pos", &Rrow, frame.rows);
    cv::createTrackbar("col", "Roi_pos", &Rcol, frame.cols);

    while(1){
        if(Rx + Rcol >= frame.cols){
            Rcol = (frame.cols-1) - Rx;
        }
        if(Rcol < 1 ) Rcol = 1;

        if(Ry + Rrow > frame.rows){
            Rrow = (frame.rows-1) - Ry;
        }
        if(Rrow < 1 ) Rrow = 1;

        cv::Rect box(Rx, Ry, Rcol, Rrow);
        cv::Mat image=frame.clone();
        cv::Mat ROI=image(box);

        int totalPiksel = ROI.rows * ROI.cols;
        int ch[3]={0,0,0};

        for(int i=0; i<ROI.rows;i++){
            for(int j=0; j<ROI.cols; j++){
                ch[0] += ROI.at<cv::Vec3b>(i, j)[0];
                ch[1] += ROI.at<cv::Vec3b>(i, j)[1];
                ch[2] += ROI.at<cv::Vec3b>(i, j)[2];
            }
        }

        int mean[3]={0,0,0};
        for(int i=0; i < 3; i++){
            mean[i] = ch[i] / totalPiksel;
        }

        cv::Scalar lower(mean[0] - 30, mean[1] - 30, mean[2] - 30);
        cv::Scalar upper(mean[0] + 30, mean[1] + 30, mean[2] + 30);

        cv::Mat mask;
        cv::inRange(image, lower, upper, mask);

        cv::rectangle(image, box, cv::Scalar(0, 255, 0), 1);
        
        cv::resize(image, image, cv::Size(image.cols/2, image.rows/2));
        cv::resize(mask, mask, cv::Size(mask.cols/2, mask.rows/2));

        cv::imshow("ori", image);
        cv::imshow("mask", mask);
        
        if(cv::waitKey(1)==27) break;
    }

    return 0;
}