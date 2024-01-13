#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

bool isEqual(const Vec4i& _l1, const Vec4i& _l2) {
    Vec4i l1(_l1), l2(_l2);

    float length1 = norm(l1);
    float length2 = norm(l2);

    float product = l1[2] * l2[2] + l1[3] * l2[3];

    if (fabs(product / (length1 * length2)) < cos(CV_PI / 30))
        return false;

    float mx1 = (l1[0] + l1[2]) * 0.5f;
    float mx2 = (l2[0] + l2[2]) * 0.5f;

    float my1 = (l1[1] + l1[3]) * 0.5f;
    float my2 = (l2[1] + l2[3]) * 0.5f;
    float dist = sqrt((mx1 - mx2) * (mx1 - mx2) + (my1 - my2) * (my1 - my2));

    if (dist > std::max(length1, length2) * 0.5f)
        return false;

    return true;
}

int main() {
    // Read the image
    Mat image = imread("/home/hatfan/dataset/garis/frame_0.jpg");

    if (image.empty()) {
        cout << "Error: Unable to read the image." << endl;
        return -1;
    }

    // Convert the image to grayscale
    Mat grayscale;
    cvtColor(image, grayscale, COLOR_BGR2GRAY);

    // Apply edge detection using Canny
    Mat edges;
    Canny(grayscale, edges, 50, 150, 3);

    // Detect lines using Hough Line Transform
    vector<Vec4i> lines;
    HoughLinesP(edges, lines, 1, CV_PI / 180, 50, 50, 10);

    // Partitioning
    vector<int> labels;
    int numberOfLines = cv::partition(lines, labels, isEqual);

    // Draw the clustered lines with different colors
    Mat clusteredLines = image.clone();
    RNG rng(215526);
    for (int i = 0; i < numberOfLines; i++) {
        Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        for (size_t j = 0; j < lines.size(); j++) {
            if (labels[j] == i) {
                line(clusteredLines, Point(lines[j][0], lines[j][1]), Point(lines[j][2], lines[j][3]), color, 2);
            }
        }
    }

    // Display the clustered lines
    imshow("Clustered Lines", clusteredLines);
    waitKey(0);

    return 0;
}
