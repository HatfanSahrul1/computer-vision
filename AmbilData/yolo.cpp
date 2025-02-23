#include <iostream>
#include <opencv2/opencv.hpp>
#include "inference.h"

int main()
{
  cv::VideoCapture cap(0);

  if(!cap.isOpened()){
    return -1;
  }
  cv::Mat frame;

  bool runOnGPU = false;
  int m_size = 320;
  std::string model_path= "/home/eros/models/feb.onnx";

  Inference inf(model_path, cv::Size(m_size, m_size), "classes.txt", runOnGPU);

  Detection ball;

  int dataKe = 0;

  int y;

  while(1){
    cap>>frame;

    std::vector<Detection> output = inf.runInference(frame);
    int detections = output.size();

    for (int i = 0; i < detections; ++i)
    {
      if(output[i].class_id == 0){
        ball = output[i];
      }
      cv::rectangle(frame, ball.box, cv::Scalar(0, 255, 0), 2);
    }

    cv::imshow("otw regresiii", frame);

    if(cv::waitKey(1) == 27) break;
    
    else if(cv::waitKey(1) == 's'){
      char buffer[50];
      std::cout << "Jarak " << dataKe << "cm dlm pixel " << y << std::endl;
      std::sprintf(buffer, "%d.jpg", dataKe);
      std::string ss(buffer);
      cv::imwrite(ss, frame);
    }
    else if(cv::waitKey(1) == 't'){
      dataKe+=100;
    }
  }
}