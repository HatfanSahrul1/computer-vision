#include "opencv2/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(){
    VideoCapture capture(0);
    if(!capture.isOpened())
    printf("Error when reading file");
    namedWindow("window",1);
    for( ; ; ){
        Mat image;
        capture>>image;
        if(image.empty())
        break;

        CascadeClassifier face_cascade;
        face_cascade.load("/home/hatfan/Downloads/opencv/data/haarcascades/haarcascade_frontalface_alt.xml");
        if(!face_cascade.load("/home/hatfan/Downloads/opencv/data/haarcascades/haarcascade_frontalface_alt.xml")){
            cerr<<"Error loading xml file"<<endl;
            return 0;
        }

        vector<Rect> faces;
        face_cascade.detectMultiScale(image,faces,1.1,2,0|CASCADE_SCALE_IMAGE,Size(24,24));

        for(int i=0;i<faces.size();i++){
            Point center(faces[i].x+faces[i].width*0.5,faces[i].y+faces[i].height*0.5);
            //ellipse(image, center,Size(faces[i].width*0.5,faces[i].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);
            rectangle(image, faces[i], Scalar(255, 0, 255), 4, 8, 0);
        }

        // Display the number of faces detected
        string text = "Faces detected: " + to_string(faces.size());
        putText(image, text, Point(10, 450), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

        imshow("Detected Face",image);
        waitKey(1);

        if(faces.size()>=2/*&&!isTerminalOpen()*/){
            system("gnome-terminal");
            waitKey(1);
        }
    }
    return 0;
}