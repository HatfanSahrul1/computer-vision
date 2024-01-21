#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//#include <opencv2/core/xml.hpp>

// #include <thread>

#include <iostream>

using namespace std;
using namespace cv;

bool isEditing=false;
int morph_size = 1;

void onTrackbar(int, void*){}

void morphsizing(){
    
}

int main() {

    // thread p1(morphsizing);
    int h = 0, l = 200, s = 0;
    int H = 180, L = 255, S = 255;
    
    string path = "/home/hatfan/dataset";///home/hatfan/dataset_garis1/dataset_garis/images/train
    stringstream filename, writeName, name, ann;

    // p1.join();    
    namedWindow("morphSize",WINDOW_AUTOSIZE);
    // createTrackbar("morphSize","morphSize",&morph_size,15,0);
    int i=0;
    while (i <1460) {
        filename.str("");
        name.str("");
        writeName.str("");
        ann.str("");
        int a;
        filename << path << "/garis/frame_" << i << ".jpg";
        ann<< path << "/gairs/frame_" << i << ".xml";
        name << "frame_" << i << ".jpg";  

        cv::Mat img_gray = cv::imread(filename.str(), 1);

        if (img_gray.empty()) {
            cout << name.str() << " not found" << endl;
            i++;
            // continue;
        }

        // FileStorage fs(ann.str(), FileStorage::READ);
        // vector<Rect> boundingBoxes;
        // fs[ann.str()] >> boundingBoxes;
        // fs.release();


        Mat hls, mask;
        cvtColor(img_gray, hls, COLOR_BGR2HLS);


            Mat element = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1)); //, Point(morph_size, morph_size));
            morphologyEx(hls, hls, MORPH_CLOSE, element, Point(-1, -1), 2);

            inRange(hls, Scalar(0, 150, 0), Scalar(180, 255, 255), mask);
            // cv::imshow(name.str(), mask);
            writeName << path << "/mask/frame_" << i << ".jpg";
            imwrite(writeName.str(), mask);
 

        // for (const Rect& box : boundingBoxes) {
        //     rectangle(mask, box, Scalar(0, 255, 0), 2);  // Green rectangle
        // }
        // a = waitKey(30);

        // if (a == 32) {
        //     // Save the processed image
        //     writeName << path << "/mask/frame_" << i << ".jpg";
        //     cv::imwrite(writeName.str(), mask);
        //      cv::destroyWindow(name.str());
        //     i++;
        //     //cout << "Image saved: " << writeName.str() << endl;
        // } else if (a == 27) {
        //     cout << "kurang pas: " << name.str() << endl;
        //     cv::destroyWindow(name.str());
        //     i++;
        // }else if (a == 97) {
        //     cv::destroyWindow(name.str());
        //     i--;
        // }

        // Clear stringstream variables for the next iteration
        filename.str("");
        name.str("");
        writeName.str("");
        ann.str("");
        i++;

        // cv::destroyWindow(name.str());
        
       
    }
    

    return 0;
}
