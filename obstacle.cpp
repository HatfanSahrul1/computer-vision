#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(Mat& img, Rect box);

vector<Rect> rectangles;  // Vector to store rectangles
vector<int> kiri;
vector<int> kanan;
RNG g_rng(0);  // Generate random number
Mat srcImage;
void directionLine(Point& end_point, Mat& frame);

int a, dest_line, area, mid;
const Point start_point=Point(319, 479);
Point end_point[]={Point(0, 239), Point(0, 0), Point(159, 0), Point(319, 0), Point(479, 0), Point(639, 0), Point(639, 239)};
// Box[] obs;

int main(int argc, char** aegv) {
    VideoCapture cap(0);
    Mat frame(480, 640, CV_8UC3);

    namedWindow("i");
    setMouseCallback("i", on_MouseHandle, (void*)&srcImage);

    a=3;
    area=640;
    mid=319;
    int n1,n2;
    
    while (true) {
        cap >> frame;
        resize(frame, frame, Size(640, 480));
        line(frame, Point(319, 0), Point(319, 479), Scalar(0, 255, 0), 1, LINE_4);
        line(frame, Point(0, 239), Point(659, 239), Scalar(0, 255, 0), 1, LINE_4);

        line(frame, Point(159, 0), Point(159, 239), Scalar(180, 180, 0), 1, LINE_4);
        line(frame, Point(479, 0), Point(479, 239), Scalar(180, 180, 0), 1, LINE_4);

       
        for(int i=0;i<rectangles.size();i++){
            area-=rectangles[i].width;
            if(rectangles[i].x+rectangles[i].width<mid && rectangles[i].x<mid){
                cout<<"box "<<i<<" di kiri"<<endl;
            }else if(rectangles[i].x<mid && rectangles[i].x+rectangles[i].width>mid ){
                int p1=mid-rectangles[i].x;
                int p2=(rectangles[i].x+rectangles[i].width)-mid;
                // cout<<p1<<"\t"<<p2<<endl;
                n1=320-p1;
                n2=320-p2;
                // cout<<n1<<"\t"<<n2<<endl;
                if(n1>n2){
                    cout<<"box "<<i<<" lebih dominan ke kanan"<<endl;
                }if(n1<n2){
                    cout<<"box "<<i<<" lebih dominan ke kiri"<<endl;
                }
            }else if(rectangles[i].x>mid && rectangles[i].x+rectangles[i].width>mid ){
                cout<<"box "<<i<<" di kanan"<<endl;
            }
        }

        // Create individual Mats for each quadrant (excluding 3rd and 4th)
        Mat r1 = frame(Rect(0, 0, frame.cols / 4, frame.rows / 2));
        Mat r2 = frame(Rect(frame.cols / 4, 0, frame.cols / 4, frame.rows / 2));
        Mat r3 = frame(Rect(frame.cols / 2, 0, frame.cols / 4, frame.rows / 2));
        Mat r4 = frame(Rect((frame.cols /4)*3, 0, frame.cols / 4, frame.rows / 2));   
        // int x;
        // float pr_R1, pr_R2, pr_R3, pr_R4;
        
        r1 = Mat::zeros(r1.size(), CV_8UC1);
        r2 = Mat::zeros(r2.size(), CV_8UC1);
        r3 = Mat::zeros(r3.size(), CV_8UC1);
        r4 = Mat::zeros(r4.size(), CV_8UC1);
        // r1=(((r1.cols*r1.rows)-x)/(r1.cols*r1.rows))*100;
        // r2=(((r1.cols*r1.rows)-x)/(r1.cols*r1.rows))*100;
        // r3=(((r1.cols*r1.rows)-x)/(r1.cols*r1.rows))*100;
        // r4=(((r1.cols*r1.rows)-x)/(r1.cols*r1.rows))*100;

        // Display the individual Mats
        imshow("r 1", r1);
        imshow("r 2", r2);
        imshow("r 3", r3);
        imshow("r 4", r4);

        for (const Rect& rect : rectangles) {
            DrawRectangle(frame, rect);
            // Box.push_back(rect);
        }


		directionLine(end_point[a], frame);
        imshow("i", frame);
        char key = waitKey(30);
        if (key == 27)
            break;
        else if (key == 'r') {
            rectangles.clear();  // Clear all bounding boxes when 'r' is pressed
        } else if (key == 'n') {
            a++;
            a = a % 7;
        }
    }

    cap.release();
    destroyAllWindows();

    return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param) {
    Mat& image = *(cv::Mat*)param;
    switch (event) {
    case EVENT_LBUTTONDOWN: {  // when the left mouse button is pressed down,
                              // get the starting corner's coordinates of the rectangle
        rectangles.push_back(Rect(x - 5, y - 5, 100, 100));
    } break;
    }
}

void DrawRectangle(Mat& img, Rect box) {
    // Draw a rectangle with random color
    rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
    // cout << box.x << "\t" << box.x + box.width << endl;
}

void directionLine(Point& end_point, Mat& frame) {
    line(frame, start_point, end_point, Scalar(0, 0, 255));
}
