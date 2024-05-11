#include <iostream>
#include <vector>
#include <getopt.h>

#include <string.h>
#include <time.h>

#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include "inference.h"

using namespace std;
using namespace cv;

double fps;

struct TimeCounter {
  public:
    TimeCounter() : reset(true) {}
  
    float Count() {
      if (reset) {
        previous_time   = std::chrono::system_clock::now();
        reset = false;
      }

      current_time = std::chrono::system_clock::now();
      elapsed_time = current_time - previous_time;

      return elapsed_time.count();
    }

    void Reset() { 
      reset = true; 
    }

  private:
    std::chrono::time_point<std::chrono::system_clock> current_time, previous_time;
    std::chrono::duration<float> elapsed_time;

    bool reset;
};

int main(int argc, char **argv)
{
    TimeCounter time;
    VideoCapture cap(2);
    const string videoStreamAddress = "https://10.252.133.72:8080/videofeed?something.mjpeg";
    // cap.open(videoStreamAddress);

    if(!cap.isOpened()){
        cap.open(0);
    }
    // else{
    //     cap.open(0);
    // }
    std::string projectBasePath = "/home/hatfan"; // Set your ultralytics base path

    bool runOnGPU = false;

    //
    // Pass in either:
    //
    // "yolov8s.onnx" or "yolov5s.onnx"
    //
    // To run Inference with yolov8/yolov5 (ONNX)
    //

    // Set white balance (if supported)
    int whiteBalanceValue = 4000;  // Adjust this value accordingly
    namedWindow("WBT",WINDOW_GUI_NORMAL);
    createTrackbar("wb","WBT",&whiteBalanceValue,6200);
    cap.set(cv::CAP_PROP_AUTO_WB, 0);  // Turn off auto white balance

    // Get white balance (if supported)
    double currentWhiteBalance = cap.get(cv::CAP_PROP_WB_TEMPERATURE);
    std::cout << "Current White Balance: " << currentWhiteBalance << std::endl;

    // Vector<string> classes{}
    // Note that in this example the classes are hard-coded and 'classes.txt' is a place holder.
    Inference inf(projectBasePath + "/best.onnx", cv::Size(640/2, 640/2), "classes.txt", runOnGPU);

    std::vector<std::string> imageNames;
    imageNames.push_back(projectBasePath + "/ultralytics/assets/bus.jpg");
    imageNames.push_back(projectBasePath + "/ultralytics/assets/zidane.jpg");

    int num_frames=0;
    clock_t start,end;

    double ms,fpsLive;

    while(true)
    {   
        if(time.Count() >= 1){
            fprintf(stderr, "FPS >> %d\n\n", num_frames);
            num_frames = 0;
            time.Reset();
        }
        num_frames++;
       start=clock(); 

        fps=cap.get(CAP_PROP_FPS);
        // string str=to_string(fps);
        // cout<<fps<<endl;

        cap.set(cv::CAP_PROP_WB_TEMPERATURE, whiteBalanceValue);

        //InitFont(FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0.0, 1, 8);

        cv::Mat frame;//= cv::imread(cap);
        cap>>frame;
        // Inference starts here...
        

        Mat hls, mask;
        // cvtColor(frame, hls, COLOR_BGR2HLS);
        // mask=Mat::zeros(640, 480, CV_8UC3);

        // Mat element = getStructuringElement(MORPH_RECT, Size(3,3));//, Point(morph_size, morph_size));
        // morphologyEx(hls, hls, MORPH_CLOSE, element, Point(-1, -1), 2);

        // inRange(hls, Scalar(0, 150, 0), Scalar(180, 255, 255), mask);

        // cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);


        std::vector<Detection> output = inf.runInference(frame);

        // cv::putText(frame, str, Point(20, 20), FONT_HERSHEY_DUPLEX,1, Scalar(255, 0, 0),2, 0);

        int detections = output.size();
        std::cout << "Number of detections:" << detections;

        for (int i = 0; i < detections; ++i)
        {
            Detection detection = output[i];

            cv::Rect box = detection.box;
            cv::Scalar color = detection.color;
            // cout<<"\n"<<box.x<<"\t"<<box.y<<endl;
            // Detection box
            cv::rectangle(frame, box, color, 2);

            // Detection box text
            std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
            cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
            cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);

            cv::rectangle(frame, textBox, color, cv::FILLED);
            cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
        }
        // Inference ends here...
        end=clock();
        // This is only for preview purposes
        float scale = 0.8;
        cv::resize(frame, frame, cv::Size(frame.cols*scale, frame.rows*scale));

        double sc=(double(end)-double(start))/double(CLOCKS_PER_SEC);
        fpsLive=double(num_frames)/double(sc);
        cout<<"\t"<<fpsLive<<endl;

        cv::imshow("Inference", frame);
        // cv::imshow("mask", mask);
    
        if(waitKey(30)==27)break;
    }
}
