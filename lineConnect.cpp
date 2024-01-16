#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//hsv
int hsv_hl=100,hsv_sl=50,hsv_vl=50;
int hsv_hh=130,hsv_sh=255,hsv_vh=255;

//hsl
int hsl_hl=100,hsl_sl=50,hsl_ll=0;
int hsl_hh=130,hsl_sh=255,hsl_lh=255;

//yuv
int yuv_yl=30,yuv_ul=130,yuv_vl=60;
int yuv_yh=210,yuv_uh=200,yuv_vh=255;

void onTrackbar(int,void*){

}

int main(){
    
    Mat img=imread("/home/hatfan/test2/bolatest.jpg",IMREAD_COLOR);

    namedWindow("hsv",WINDOW_AUTOSIZE);
    namedWindow("hsl",WINDOW_AUTOSIZE);
    namedWindow("yuv",WINDOW_AUTOSIZE);

    // createTrackbar("hsv_hl","hsv",&hsv_hl,255,onTrackbar);
    // createTrackbar("hsv_hh","hsv",&hsv_hh,255,onTrackbar);
    // createTrackbar("hsv_sl","hsv",&hsv_sl,255,onTrackbar);
    // createTrackbar("hsv_sh","hsv",&hsv_sh,255,onTrackbar);
    // createTrackbar("hsv_vl","hsv",&hsv_vl,255,onTrackbar);
    // createTrackbar("hsv_vh","hsv",&hsv_vh,255,onTrackbar);
    
    // createTrackbar("hsl_hl","hsl",&hsl_hl,255,onTrackbar);
    // createTrackbar("hsl_hh","hsl",&hsl_hh,255,onTrackbar);
    // createTrackbar("hsl_sl","hsl",&hsl_sl,255,onTrackbar);
    // createTrackbar("hsl_sh","hsl",&hsl_sh,255,onTrackbar);
    // createTrackbar("hsl_ll","hsl",&hsl_ll,255,onTrackbar);
    // createTrackbar("hsl_lh","hsl",&hsl_lh,255,onTrackbar);
    
    // createTrackbar("yuv_yl","yuv",&yuv_yl,255,onTrackbar);
    // createTrackbar("yuv_yh","yuv",&yuv_yh,255,onTrackbar);
    // createTrackbar("yuv_ul","yuv",&yuv_ul,255,onTrackbar);
    // createTrackbar("yuv_uh","yuv",&yuv_uh,255,onTrackbar);
    // createTrackbar("yuv_vl","yuv",&yuv_vl,255,onTrackbar);
    // createTrackbar("yuv_vh","yuv",&yuv_vh,255,onTrackbar);
    

    Mat hsv,chsv;
    cvtColor(img,hsv,COLOR_BGR2HSV);
    //Canny(hsv,chsv,15,30,7);

    Mat yl,cyl;
    cvtColor(img,yl,COLOR_BGR2HLS);
    //Canny(yl,cyl,15,30,7);

    // Mat lab,clab;
    // cvtColor(img,lab,COLOR_BGR2Lab);
    // Canny(lab,clab,15,30,7);

    vector<Mat> chl;
    split(img,chl);

    Mat ch=chl[0];

    Mat yuv,cyuv;
    cvtColor(ch,yuv,COLOR_BGR2YUV);
    //Canny(yuv,cyuv,15,30,7);



    // for(;;){
    //     inRange(hsv,Scalar(hsv_hl,hsv_sl,hsv_vl),Scalar(hsv_hh,hsv_sh,hsv_vh),chsv);
    //     inRange(yl,Scalar(hsl_hl,hsl_sl,hsl_ll),Scalar(hsl_hh,hsl_sh,hsl_lh),cyl);
    //     inRange(yuv,Scalar(yuv_yl,yuv_ul,yuv_vl),Scalar(yuv_yh,yuv_uh,yuv_vh),cyuv);
    //     //cout<<yuv_vh<<endl;
    //     if(waitKey(50)==27) break;
    // imshow("ori",img);
    // imshow("hsv",chsv);
    // imshow("hsl",cyl);
    // //imshow("lab",clab);
    // imshow("yuv",cyuv);
    // }
    imshow("y",yuv);
   

    waitKey(0);
    return 0;
}