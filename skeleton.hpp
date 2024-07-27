/*
 * Skeletonization.hpp
 *
 *  Created on: Oct 2, 2014
 *      Author: Raghu
 *
 *  Code for thinning a binary image using Zhang-Suen algorithm.
 */

#ifndef SKELETONIZATION_HPP_INCLUDED
#define SKELETONIZATION_HPP_INCLUDED

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

/**
 * Perform one thinning iteration.
 * Normally you wouldn't call this function directly from your code.
 */
void thinningIteration(Mat& im, int iter)
{
    Mat marker = Mat::zeros(im.size(), CV_8UC1);

    for (int i = 1; i < im.rows-1; i++)
    {
        for (int j = 1; j < im.cols-1; j++)
        {
            uchar p2 = im.at<uchar>(i-1, j);
            uchar p3 = im.at<uchar>(i-1, j+1);
            uchar p4 = im.at<uchar>(i, j+1);
            uchar p5 = im.at<uchar>(i+1, j+1);
            uchar p6 = im.at<uchar>(i+1, j);
            uchar p7 = im.at<uchar>(i+1, j-1);
            uchar p8 = im.at<uchar>(i, j-1);
            uchar p9 = im.at<uchar>(i-1, j-1);

            int A  = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
                     (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
                     (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
                     (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
            int B  = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
            int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
            int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);

            if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
                marker.at<uchar>(i,j) = 1;
        }
    }

    im &= ~marker;
}

/**
 * Function for thinning the given binary image
 */
void thinning(Mat& im)
{
    im /= 255;

    Mat prev = Mat::zeros(im.size(), CV_8UC1);
    Mat diff;

    do {
        thinningIteration(im, 0);
        thinningIteration(im, 1);
        absdiff(im, prev, diff);
        im.copyTo(prev);
    }
    while (countNonZero(diff) > 0);

    im *= 255;
}

void CleaningBorder(Mat &result){
    for(int i=0;i<result.rows;i++){
        for(int j=0;j<result.cols;j++){
            result.at<uchar>(i, 0) = 0;
            result.at<uchar>(0, j) = 0;
            result.at<uchar>(i, result.cols-1) = 0;
            result.at<uchar>(result.rows, j) = 0;
        }
    }
}

/**
 * This is the function that acts as the input/output system of this header file.
 */
Mat skeletonization(Mat inputImage)
{
    if (inputImage.empty())
    	cout<<"Inside skeletonization, Source empty"<<endl;

    Mat outputImage;
    cvtColor(inputImage, outputImage, COLOR_BGR2GRAY);
    threshold(outputImage, outputImage, 0, 255, THRESH_BINARY+THRESH_OTSU);

    thinning(outputImage);
    CleaningBorder(outputImage);

    return outputImage;
}

void Coloring(Mat &mat, Mat &output){
    // output = Mat::zeros(mat.size(), CV_8UC3);
    cvtColor(mat, output, COLOR_GRAY2BGR);
    for(int i=0;i<mat.rows;i++){
        for(int j=0;j<mat.cols;j++){
            if(mat.at<char>(i, j)){
                output.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
            }
        }
    }

    // mat = temp;
}

void HoughlineProb(Mat &input, Mat &output){
    vector<Vec4i> lines;
    HoughLinesP(input, lines, 1, CV_PI / 180, 20, 2, 50);

    // Draw the lines on the original image
    
    for (size_t i = 0; i < lines.size(); i++) {
        cout<<i<<endl;
        Vec4i l = lines[i];
        line(output, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
    }
}

void HoughlineProb(Mat &input, Mat &output, int thresh, int minLineLength, int maxLineGap){
    vector<Vec4i> lines;
    HoughLinesP(input, lines, 1, CV_PI / 180, thresh, minLineLength, maxLineGap);

    // Draw the lines on the original image
    
    for (size_t i = 0; i < lines.size(); i++) {
        cout<<i<<endl;
        Vec4i l = lines[i];
        line(output, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
    }
}

void HoughlineRegular(Mat &input, Mat &output,int thresh){
    vector<Vec2f> lines;
    HoughLines(input, lines, 1, CV_PI / 180, thresh);

    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(output, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
    }
}




#endif /* PROXYMAIN3_HPP_ */
