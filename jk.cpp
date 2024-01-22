#include <opencv2/opencv.hpp>
#include <fstream>
#include <sstream>

int main() {
    // Replace "your_annotations.txt" with the actual path to your text file
    std::ifstream inputFile("/home/hatfan/dataset/frame_0.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the text file." << std::endl;
        return -1;
    }

    // Read and process bounding box annotations
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int label;
        double x, y, width, height;

        if (!(iss >> label >> x >> y >> width >> height)) {
            std::cerr << "Error: Failed to parse line in the text file." << std::endl;
            continue; // Skip to the next line
        }

        // Assuming your image is in "your_image.jpg"
        cv::Mat img = cv::imread("/home/hatfan/dataset/frame_0.jpg");

        if (img.empty()) {
            std::cerr << "Error: Could not read the image." << std::endl;
            return -1;
        }

        // Convert relative coordinates to absolute coordinates
        int imgWidth = img.cols;
        int imgHeight = img.rows;
        int xAbs = static_cast<int>(x * imgWidth);
        int yAbs = static_cast<int>(y * imgHeight);
        int widthAbs = static_cast<int>(width * imgWidth);
        int heightAbs = static_cast<int>(height * imgHeight);

        // Draw the bounding box on the image
        cv::rectangle(img, cv::Rect(xAbs, yAbs, widthAbs, heightAbs), cv::Scalar(0, 255, 0), 2);

        // Display the image with bounding box
        cv::imshow("Bounding Box", img);
        cv::waitKey(0);
    }

    // Close the file
    inputFile.close();

    return 0;
}
