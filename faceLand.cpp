#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>

int main() {
    // Load the face landmark model
    dlib::shape_predictor predictor;
    dlib::deserialize("/home/hatfan/test2/shape_predictor_68_face_landmarks.dat") >> predictor;

    // OpenCV video capture
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Couldn't open the camera." << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::namedWindow("Face Landmark Detection", cv::WINDOW_AUTOSIZE);

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        // Convert OpenCV image to dlib image
        dlib::cv_image<dlib::bgr_pixel> dlib_img(frame);

        // Detect faces
        dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
        std::vector<dlib::rectangle> faces = detector(dlib_img);

        // Draw landmarks on the faces
        for (const auto& face : faces) {
            dlib::full_object_detection shape = predictor(dlib_img, face);
            for (unsigned int i = 0; i < shape.num_parts(); ++i) {
                cv::circle(frame, cv::Point(shape.part(i).x(), shape.part(i).y()), 3, cv::Scalar(0, 255, 0), -1);
            }
        }

        // Display the frame
        cv::imshow("Face Landmark Detection", frame);

        // Break the loop if 'ESC' is pressed
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    return 0;
}
