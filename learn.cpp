/*
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Rect2d boundingBox;
bool annotateComplete=false;

void onMouse(int event,int x,int y,int flags,void* userdata){
    if(event==EVENT_LBUTTONDOWN){
        boundingBox.x=x;
        boundingBox.y=y;
    }else if(event=EVENT_LBUTTONUP){
        boundingBox.width=x-boundingBox.x;
        boundingBox.height=y-boundingBox.y;
        rectangle(*(Mat*)userdata,boundingBox,Scalar(0,255,0),2);
        imshow("Annotate Object",*(Mat*)userdata);
        annotateComplete=true;
    }
}

int main(){
    VideoCapture cap(0);

    if(!cap.isOpened()){
        cout<<"Error opening the Camera."<<endl;
        return -1;
    }

    Mat frame;

    namedWindow("Annotate Object",WINDOW_AUTOSIZE);

    cout<<"Annotate object by dragging a bounding box around it"<<endl;
    cout<<"Press 'q' to exit annotate mode"<<endl;

    while(true){
        cap>>frame;

        if(frame.empty()){
            cout<<"end of video stream"<<endl;
            break;
        }
        setMouseCallback("Annotate Object",onMouse,&frame);
        imshow("Annotate Object",frame);

        char key=waitKey(1);
        if(key=='q'){
            break;
        }

        if(annotateComplete){
            Mat annotateRegion=frame(boundingBox);
            imwrite("ann.jpg",annotateRegion);

            cout<<"Annotated region cmplt"<<endl;

            boundingBox=Rect2d();
            annotateComplete=false;
        }
    }

    while(true){
        cap>>frame;

        if(frame.empty()){
            cout<<"end of video stream"<<endl;
            break;
        }

        imshow("Real-Time Object Detection",frame);

        if(waitKey(1)==27){
            break;
        }
    }
    return 0;
}*/

/*/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Rect2d boundingBox;
int annotateCount=0;
//bool annotateComplete=false;

void onMouse(int event,int x,int y,int flags,void* userdata){
    static Mat frameCopy;
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Rect2d boundingBox;
bool annotateComplete=false;

void onMouse(int event,int x,int y,int flags,void* userdata){
    if(event==EVENT_LBUTTONDOWN){
        boundingBox.x=x;
        boundingBox.y=y;
    }else if(event=EVENT_LBUTTONUP){
        boundingBox.width=x-boundingBox.x;
        boundingBox.height=y-boundingBox.y;
        rectangle(*(Mat*)userdata,boundingBox,Scalar(0,255,0),2);
        imshow("Annotate Object",*(Mat*)userdata);
        annotateComplete=true;
    }
}

int main(){
    VideoCapture cap(0);

    if(!cap.isOpened()){
        cout<<"Error opening the Camera."<<endl;
        return -1;
    }

    Mat frame;

    namedWindow("Annotate Object",WINDOW_AUTOSIZE);

    cout<<"Annotate object by dragging a bounding box around it"<<endl;
    cout<<"Press 'q' to exit annotate mode"<<endl;

    while(true){
        cap>>frame;

        if(frame.empty()){
            cout<<"end of video stream"<<endl;
            break;
        }
        setMouseCallback("Annotate Object",onMouse,&frame);
        imshow("Annotate Object",frame);

        char key=waitKey(1);
        if(key=='q'){
            break;
        }

        if(annotateComplete){
            Mat annotateRegion=frame(boundingBox);
            imwrite("path/ann.jpg",annotateRegion);

            cout<<"Annotated region cmplt"<<endl;

            boundingBox=Rect2d();
            annotateComplete=false;
        }
    }

    while(true){
        cap>>frame;

        if(frame.empty()){
            cout<<"end of video stream"<<endl;
            break;
        }

        imshow("Real-Time Object Detection",frame);

        if(waitKey(1)==27){
            break;
        }
    }
    return 0;
}
    if(event=EVENT_LBUTTONDOWN){
        boundingBox.x=x;
        boundingBox.y=y;
        frameCopy=(*(Mat*)userdata).clone();
    }else if(event==EVENT_LBUTTONUP){
        boundingBox.width=x-boundingBox.x;
        boundingBox.height=y-boundingBox.y;
        rectangle(frameCopy,boundingBox,Scalar(0,255,0),2);
        imshow("Annotate Object",frameCopy);
        annotateCount++;

        Mat annotateRegion=(*(Mat*)userdata)(boundingBox);
        stringstream filename;
        filename<<"annotate_"<<annotateCount<<".jpg";
        imwrite("path/"+filename.str(),annotateRegion);

        cout<<"saved"<<endl;
    }
}

int main(){
    VideoCapture cap(0);

    if(!cap.isOpened()){
        cout<<"Camera won't open"<<endl;
        return -1;
    }

    Mat frame;

    namedWindow("Annotate Object", WINDOW_AUTOSIZE);

    while(true){
        cap>>frame;

        if(frame.empty()){
            cout<<"end"<<endl;
            break;
        }

        setMouseCallback("Annotate Object",onMouse, &frame);
        imshow("Annotate Object", frame);

        char key=waitKey(1);
        if(key=='q'){
            break;
        }
    }
    return 0;
}*/