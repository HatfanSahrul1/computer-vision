#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;

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

int main(){
    VideoCapture cap(2);
    TimeCounter time;

    Mat frame;
    
    int fps=0;
    
    cap.set(CAP_PROP_FPS, 10);

    while(true){
        if(time.Count()>=1){
            cout<<fps<<endl;
            fps=0;
            time.Reset();
        }
        cap>>frame;

        // fps=cap.get(CAP_PROP_FPS);
        fps++;
        // cout<<fps<<endl;

        if(waitKey(1)=='x')
            break;
    }
}
