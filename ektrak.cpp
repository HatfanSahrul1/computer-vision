#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

struct MinMax {
    int min;
    int max;
};

struct ColorComponent {
    int c1;
    int c2;
    int c3;
    double dist;
};

void extractColor(Mat myROI, char colorType, std::vector<MinMax>* ret);

int main() {
    // Load an image (replace "your_image.jpg" with the actual image file path)
    Mat image = imread("your_image.jpg");

    if (image.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
        return -1;
    }

    // Define a region of interest (ROI) in the image
    Rect roiRect(100, 100, 200, 200);  // Example: x=100, y=100, width=200, height=200

    // Extract color information from the ROI using HSV color space
    char colorType = 'H';
    std::vector<MinMax> result;
    extractColor(image(roiRect), colorType, &result);

    // Display the results
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "Color Component " << i + 1 << " - Min: " << result[i].min << ", Max: " << result[i].max << std::endl;
    }

    return 0;
}

void extractColor(Mat myROI, char colorType, std::vector<MinMax>* ret) {
    ret->clear();

    Mat conv;
    if (colorType == 'H') {
        cvtColor(myROI, conv, COLOR_BGR2HSV);
    } else if (colorType == 'Y') {
        cvtColor(myROI, conv, COLOR_BGR2YUV);
    } else if (colorType == 'L') {
        cvtColor(myROI, conv, COLOR_BGR2HLS);
    } else {
        conv = myROI.clone();
    }

    std::vector<int> _1;
    std::vector<int> _2;
    std::vector<int> _3;

    std::vector<ColorComponent> euclideanValue;

    for (int i = 0; i < myROI.rows; ++i) {
        for (int j = 0; j < myROI.cols; ++j) {
            double dist = euclidean(conv.at<Vec3b>(i, j));
            int val1 = conv.at<Vec3b>(i, j)[0];
            int val2 = conv.at<Vec3b>(i, j)[1];
            int val3 = conv.at<Vec3b>(i, j)[2];
            ColorComponent temp{ val1, val2, val3, dist };
            euclideanValue.push_back(temp);
        }
    }

    // evaluateVector(&euclideanValue);

    for (size_t i = 0; i < euclideanValue.size(); ++i) {
        _1.push_back(euclideanValue[i].c1);
        _2.push_back(euclideanValue[i].c2);
        _3.push_back(euclideanValue[i].c3);
    }

    ret->push_back(getMinMax(_1));
    ret->push_back(getMinMax(_2));
    ret->push_back(getMinMax(_3));
}