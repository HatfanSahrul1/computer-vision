#include <opencv2/opencv.hpp>
#include <numeric>

using namespace std;
using namespace cv;

bool extendedBoundingRectangleLineEquivalence(const Vec4i& _l1, const Vec4i& _l2, float extensionLengthFraction, float maxAngleDiff, float boundingRectangleThickness);

Vec2d linearParameters(Vec4i line);

Vec4i extendedLine(Vec4i line, double d);

std::vector<Point2i> boundingRectangleContour(Vec4i line, float d);

int main(int argc, const char* argv[]) {
    /*if (argc < 2) {
        std::cout << "img filepath should be present in args" << std::endl;
        return -1;
    }*/

    Mat image = imread("/home/hatfan/test2/b.jpg");
    Mat smallerImage;
    resize(image, smallerImage, cv::Size(), 0.5, 0.5, INTER_CUBIC);
    Mat target = smallerImage.clone();

    namedWindow("Detected Lines", WINDOW_NORMAL);
    namedWindow("Reduced Lines", WINDOW_NORMAL);
    Mat detectedLinesImg = Mat::zeros(target.rows, target.cols, CV_8UC3);
    Mat reducedLinesImg = detectedLinesImg.clone();

    // detect lines using LineSegmentDetector
    Mat grayscale;
    cvtColor(target, grayscale, COLOR_BGR2GRAY);  // Use COLOR_BGR2GRAY instead of CV_BGR2GRAY
    Ptr<LineSegmentDetector> detector = createLineSegmentDetector(LSD_REFINE_NONE);
    std::vector<Vec4i> lines;
    detector->detect(grayscale, lines);

    // remove small lines
    std::vector<Vec4i> linesWithoutSmall;
    std::copy_if(lines.begin(), lines.end(), std::back_inserter(linesWithoutSmall), [](Vec4f line) {
        float length = sqrtf((line[2] - line[0]) * (line[2] - line[0]) + (line[3] - line[1]) * (line[3] - line[1]));
        return length > 30;
    });

    std::cout << "Detected: " << linesWithoutSmall.size() << std::endl;

    // partition lines based on extendedBoundingRectangleLineEquivalence
    std::vector<int> labels;
    int equivalenceClassesCount = cv::partition(linesWithoutSmall, labels, [&](const Vec4i& l1, const Vec4i& l2) {
        return extendedBoundingRectangleLineEquivalence(l1, l2, 0.2, 2.0, 10);
    });

    std::cout << "Equivalence classes: " << equivalenceClassesCount << std::endl;

    // draw original detected lines
    RNG rng(215526);
    for (int i = 0; i < linesWithoutSmall.size(); i++) {
        Vec4i& detectedLine = linesWithoutSmall[i];
        line(detectedLinesImg, cv::Point(detectedLine[0], detectedLine[1]), cv::Point(detectedLine[2], detectedLine[3]), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2);
    }

    // build point clouds out of each equivalence class
    std::vector<std::vector<Point2i>> pointClouds(equivalenceClassesCount);
    for (int i = 0; i < linesWithoutSmall.size(); i++) {
        Vec4i& detectedLine = linesWithoutSmall[i];
        pointClouds[labels[i]].push_back(Point2i(detectedLine[0], detectedLine[1]));
        pointClouds[labels[i]].push_back(Point2i(detectedLine[2], detectedLine[3]));
    }

    // fit line to each equivalence class point cloud and draw the reduced lines
    std::vector<Vec4i> reducedLines = std::accumulate(pointClouds.begin(), pointClouds.end(), std::vector<Vec4i>{}, [&](std::vector<Vec4i> target, const std::vector<Point2i>& pointCloud) {
        Vec4f lineParams;
        fitLine(pointCloud, lineParams, DIST_L2, 0, 0.01, 0.01);  // Use DIST_L2 instead of CV_DIST_L2
        target.push_back(Vec4i(lineParams[2], lineParams[3], lineParams[2] + 100 * lineParams[0], lineParams[3] + 100 * lineParams[1]));
        return target;
    });

    // draw the reduced lines
    for (Vec4i reduced : reducedLines) {
        line(reducedLinesImg, Point(reduced[0], reduced[1]), Point(reduced[2], reduced[3]), Scalar(255, 255, 255), 2);
    }

    imshow("Detected Lines", detectedLinesImg);
    imshow("Reduced Lines", reducedLinesImg);
    waitKey(0);

    return 0;
}

bool extendedBoundingRectangleLineEquivalence(const Vec4i& _l1, const Vec4i& _l2, float extensionLengthFraction, float maxAngleDiff, float boundingRectangleThickness) {
    // Implementation here
    return false;
}

Vec2d linearParameters(Vec4i line) {
    // Implementation here
    return Vec2d();
}

Vec4i extendedLine(Vec4i line, double d) {
    // Implementation here
    return Vec4i();
}

std::vector<Point2i> boundingRectangleContour(Vec4i line, float d) {
    // Implementation here
    return std::vector<Point2i>();
}
