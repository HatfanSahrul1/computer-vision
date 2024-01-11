#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

//Mat img, res, element;

int main(int argc, char** argv)
{
    /*namedWindow( "Meanshift", 0 );
    img = imread("/home/hatfan/test2/stuff.jpg");
    GaussianBlur(img, img, Size(5,5), 2, 2);
    pyrMeanShiftFiltering( img, res, 20, 45, 3);
    imwrite("/home/hatfan/test2/meanshift.png", res);
    imshow( "Meanshift", res );
    waitKey();*/
    VideoCapture cap;

    Mat frame;

    namedWindow("test",WINDOW_AUTOSIZE);

    while(true){
        cap>>frame;

        GaussianBlur(frame,frame,Size(5,5),2,2);

        Mat res;
        pyrMeanShiftFiltering(frame,res,20,45,3);

        imshow("test",frame);
        imshow("res",res);

        waitKey();
    }
    return 0;
}