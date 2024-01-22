#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME "Drawing Rectangle"
#define IMAGE_PATH "/home/hatfan/test2/L.jpeg"

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(Mat& img, Rect box);
void roiPart1(Mat& img, Rect box);
void GetStandardDeviation(cv::Mat &roi, uint8_t *mean, uint8_t *sd);
void GetColorBoundaries(cv::Mat &roi, Scalar &lower, Scalar &upper);
void GetMean(cv::Mat &roi, uint8_t *mean);

Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(0);  // Generate random number

int main(int argc, char** argv) {
	Mat srcImage(600, 800, CV_8UC3);
	Mat tempImage;
	srcImage = imread(IMAGE_PATH);
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*) &srcImage);
	while (1) {
		srcImage.copyTo(tempImage);
		if (g_bDrawingBox)
			DrawRectangle(tempImage, g_rectangle);
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27)  // stop drawing rectanglge if the key is 'ESC'
			break;
	}
	return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param) {
	Mat& image = *(cv::Mat*) param;
	switch (event) {
	case EVENT_MOUSEMOVE: {    // When mouse moves, get the current rectangle's width and height
		if (g_bDrawingBox) {
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
		break;
	case EVENT_LBUTTONDOWN: {  // when the left mouse button is pressed down,
		                       //get the starting corner's coordinates of the rectangle
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0);
	}
		break;
	case EVENT_LBUTTONUP: {   //when the left mouse button is released,
		                      //draw the rectangle
		g_bDrawingBox = false;
		if (g_rectangle.width < 0) {
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}

		if (g_rectangle.height < 0) {
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		// DrawRectangle(image, g_rectangle);
        roiPart1(image, g_rectangle);
	}
		break;
	}
}
void DrawRectangle(Mat& img, Rect box)
{
	//Draw a rectangle with random color
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255),
					g_rng.uniform(0,255),g_rng.uniform(0,255)));
}

void roiPart1(Mat& frame,Rect box){
    Mat img=imread(IMAGE_PATH);
    Mat roi;
	uint8_t a=0, sd=0;

    // Rect rect(img.cols/4,img.rows/4, img.cols/2,img.rows/2);

    // rectangle(img,rect,Scalar(255),2,8,0);

    // imshow("img",img);
	Scalar lower,upper;
    roi=frame(box);

    imshow("img2",roi);

	GetColorBoundaries(roi,lower,upper);
	Mat mask;
	inRange(img, lower, upper,mask);
	imshow("g",mask);
}

void GetMean(cv::Mat &roi, uint8_t *mean) {
  unsigned int sum[3] = {0, 0, 0};

  for (short i = 0; i < roi.rows; ++i) {
    for (short j = 0; j < roi.cols; ++j) {
      sum[0] += roi.at<cv::Vec3b>(i, j)[0];
      sum[1] += roi.at<cv::Vec3b>(i, j)[1];
      sum[2] += roi.at<cv::Vec3b>(i, j)[2];
    }
  }

  unsigned int total_pixels = (roi.rows * roi.cols);

  for (uint8_t i = 0; i < 3; ++i) {
    sum[i] /= total_pixels;

    if (sum[i] > 255)
      sum[i] = 255;

    mean[i] = sum[i];
  }
}

void GetColorBoundaries(cv::Mat &roi, Scalar &lower, Scalar &upper) {
  cv::GaussianBlur(roi, roi, cv::Size(3, 3), -1, -1);

  uint8_t mean[3];
  GetMean(roi, mean);

  uint8_t sd[3]; // standard deviation
  GetStandardDeviation(roi, mean, sd);

  short min;
  short max;

  for (uint8_t i = 0; i < 3; ++i) {
    min = mean[i] - sd[i];
    max = mean[i] + sd[i];
    
    if (min < 0)
      min = 0;

    if (max > 255)
      max = 255;

    lower[i] = min;
    upper[i] = max;

  }
}

void GetStandardDeviation(cv::Mat &roi, uint8_t *mean, uint8_t *sd) {
  unsigned int delta[3] = {0, 0, 0};

  for (short i = 0; i < roi.rows; ++i) {
    for (short j = 0; j < roi.cols; ++j) {
      delta[0] += pow((roi.at<cv::Vec3b>(i, j)[0] - mean[0]), 2);
      delta[1] += pow((roi.at<cv::Vec3b>(i, j)[1] - mean[1]), 2);
      delta[2] += pow((roi.at<cv::Vec3b>(i, j)[2] - mean[2]), 2);
    }
  }

  unsigned int total_pixels = roi.rows * roi.cols;

  for (uint8_t i = 0; i < 3; ++i) {
    delta[i] /= total_pixels - 1; // reduce by 1 because reducing bias
    delta[i] = sqrt(delta[i]);

    if (delta[i] > 255)
      delta[i] = 255;

    sd[i] = delta[i];
  }
}