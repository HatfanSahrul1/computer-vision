#include "opencv2/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(){
    Mat image;
    image=imread("/home/hatfan/test2/try.jpg", IMREAD_COLOR);

    namedWindow("window1",1);
    imshow("window1",image);

    CascadeClassifier face_cascade;
    face_cascade.load("/home/hatfan/Downloads/opencv/data/haarcascades/haarcascade_frontalface_alt.xml");


    if(!face_cascade.load("/home/hatfan/Downloads/opencv/data/haarcascades/haarcascade_frontalface_alt.xml")){
        cerr<<"Error Loading XML file"<<endl;
        return 0;
    }

    vector<Rect> faces;
    face_cascade.detectMultiScale(image,faces,1.1,2,0|CASCADE_SCALE_IMAGE,Size(30,03));

    for(int i=0;i<faces.size();i++){
        Point center(faces[i].x+faces[i].width*0.5,faces[i].y+faces[i].height*0.5);
        ellipse(image, center,Size(faces[i].width*0.5,faces[i].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);
    }
    imshow("Detected Face",image);
    waitKey(0);
    return 0;
    
}