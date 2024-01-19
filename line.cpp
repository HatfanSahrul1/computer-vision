#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;



int th=150,minLength=0,maxGap=0;

int p_th=50,p_minLength=50,p_maxGap=10;

void onTrackbar(int, void*){
    //empty trackbar callback
}

int main(int argc, char** argv)
{
    namedWindow("regular",WINDOW_NORMAL);
    namedWindow("prob",WINDOW_NORMAL);

    createTrackbar("Threshold","regular",&th,300,onTrackbar,NULL);
    createTrackbar("minLength","regular",&minLength,300,onTrackbar,NULL);
    createTrackbar("maxGap","regular",&maxGap,300,onTrackbar,NULL);
    
    createTrackbar("Threshold","prob",&p_th,300,onTrackbar,NULL);
    createTrackbar("minLength","prob",&p_minLength,300,onTrackbar,NULL);
    createTrackbar("maxGap","prob",&p_maxGap,300,onTrackbar,NULL);
    

    // VideoCapture cap(0);
    // const string videoStreamAddress = "https://10.252.133.72:8080/videofeed?something.mjpeg";
    // cap.open(videoStreamAddress);
    // Declare the output variables
    Mat dst, cdst, cdstP;
    const char* default_file = "/home/hatfan/test2/gbr/chessboard_12.jpg";
    const char* filename = argc >=2 ? argv[1] : default_file;
    // Loads an image
    Mat src = imread( samples::findFile( filename ), IMREAD_COLOR );
    Mat bil;
    GaussianBlur(src,bil,Size(5,5),9,18,BORDER_DEFAULT);
    Mat hsv, mask;//khusus putih
    cvtColor(bil,hsv,COLOR_BGR2HSV);
    inRange(hsv,Scalar(20,0,200),Scalar(225,30,255),mask);

    // Check if image is loaded fine
    //src=Mat::ones(720,720,CV_8UC3);
    //Mat src;
    /*if(src.empty()){
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default %s] \n", default_file);
        return -1;
    }*/
        //GaussianBlur(src, src, Size(5, 5), 2, 2);
    // Edge detection
    while(true){
        //cap>>src;
    

        Canny(mask, dst, 40, 200, 3);
        // Copy edges to the images that will display the results in BGR
        cvtColor(dst, cdst, COLOR_GRAY2BGR);
        cdstP = cdst.clone();
        // Standard Hough Line Transform
        vector<Vec2f> lines; // will hold the results of the detection
        HoughLines(dst, lines, 1, CV_PI/180, th, minLength, maxGap ); // runs the actual detection
        // Draw the lines
        for( size_t i = 0; i < lines.size(); i++ )
        {
            float rho = lines[i][0], theta = lines[i][1];
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000*(-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000*(a));
            line( cdst, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
        }
        // Probabilistic Line Transform
        vector<Vec4i> linesP; // will hold the results of the detection
        HoughLinesP(dst, linesP, 1, CV_PI/180, p_th, p_minLength, p_maxGap ); // runs the actual detection
        // Draw the lines
        for( size_t i = 0; i < linesP.size(); i++ )
        {
            Vec4i l = linesP[i];
            line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
        }
        // Show results
        imshow("Source", bil);
        imshow("regular", cdst);
        imshow("prob", cdstP);
        // Wait and Exit
        if(waitKey(30)==27) break;
        
    }
    return 0;
}