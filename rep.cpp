#include <opencv2/opencv.hpp>
#include <string.h>


using namespace std;
using namespace cv;

void onTrackbar(int, void*){}

int main() {

    int h=0,l=200,s=0;
    int H=180,L=255,S=255;
    // namedWindow("s",WINDOW_AUTOSIZE);

    // createTrackbar("h","s",&h,255,onTrackbar);
    // createTrackbar("H","s",&H,255,onTrackbar);
    // createTrackbar("l","s",&l,255,onTrackbar);
    // createTrackbar("L","s",&L,255,onTrackbar);
    // createTrackbar("s","s",&s,255,onTrackbar);
    // createTrackbar("S","s",&S,255,onTrackbar);

    string path="/home/hatfan/dataset";
    stringstream filename,writeName,name;
    for(int i=0;i<1460;i++){
        int a;
        filename<<path<<"/garis/frame_"<<i<<".jpg";
        name<<"frame_"<<i<<".jpg";

        cv::Mat img_gray=cv::imread(filename.str(),1);
        if(img_gray.empty()){
            cout<<name.str()<<"not found"<<endl;
            continue;
        }
        Mat hls,mask;
        cvtColor(img_gray,hls,COLOR_BGR2HLS);

        int morph_size = 10; 
    
        Mat element = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));  
        morphologyEx(hls, hls, MORPH_CLOSE, element, Point(-1, -1), 2); 

        inRange(hls,Scalar(0,150,0),Scalar(180,255,255),mask);
        cv::imshow(name.str(),mask);

        writeName<<path<<"/mask/frame_"<<i<<".jpg";

        a = waitKey(0); 
        if(a == 32){
            cv::imwrite(writeName.str(),mask);
            cv::destroyAllWindows();
        }else if(a == 27){
            cout<<name.str()<<endl;
            cv::destroyAllWindows();
        }
    }

 return 0;
}
