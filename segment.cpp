#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat img, res, element;


void onTrackbar(int, void*);



int main(int argc, char** argv)
{
    int sp=20,sr=45,max=3;

    namedWindow( "Meanshift", 0 );
    namedWindow("set",0);

    createTrackbar("sp","set",&sp,50,onTrackbar);
    createTrackbar("sr","set",&sr,100,onTrackbar);
    createTrackbar("max","set",&sp,10,onTrackbar);
    img = imread("/home/hatfan/test2/bolatest.jpg");
    while(true){
        
        GaussianBlur(img, img, Size(5,5), 2, 2);
        pyrMeanShiftFiltering( img, res, sp, sr, max);
        //imwrite("/home/hatfan/test2/meanshift.png", res);
        imshow( "Meanshift", res );
        waitKey(27);
    }
    /*VideoCapture cap;

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
    }*/
    return 0;
}

void onTrackbar(int, void*){
    
}