#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

// Structure to store the coordinates of landmarks
struct Landmark {
    int x, y;
};

// Vector to store multiple landmarks
vector<Landmark> landmarks;

// Callback function for mouse events
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        // Record the position of the clicked point
        Landmark newLandmark = {x, y};
        landmarks.push_back(newLandmark);

        // Display the landmark on the image
        circle(*(Mat*)userdata, Point(x, y), 5, Scalar(0, 255, 0), -1);
        imshow("Image with Landmarks", *(Mat*)userdata);
    }
}

int main() {
    // Read an image from file
    Mat image = imread("/home/hatfan/test2/lpng.jpeg");

    if (image.empty()) {
        cerr << "Error loading the image!" << endl;
        return -1;
    }

    // Create a window
    namedWindow("Image with Landmarks", WINDOW_AUTOSIZE);

    // Set the callback function for mouse events
    setMouseCallback("Image with Landmarks", onMouse, &image);

    // Display the image
    imshow("Image with Landmarks", image);

    // Wait for the user to mark landmarks (press any key to exit)
    waitKey(0);

    // Print the coordinates of the marked landmarks
    for (const auto& landmark : landmarks) {
        cout << "Landmark: (" << landmark.x << ", " << landmark.y << ")" << endl;
    }

    return 0;
}
