#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>

int main() {
    // Load the face landmark model
    dlib::shape_predictor predictor;
    dlib::deserialize("/home/hatfan/test2/shape_predictor_68_face_landmarks.dat") >> predictor;

    // OpenCV read image
    cv::Mat frame = cv::imread("/home/hatfan/test2/facialExp.jpg");  // Replace with the path to your image

    if (frame.empty()) {
        std::cerr << "Error: Couldn't read the image." << std::endl;
        return -1;
    }

    // Convert OpenCV image to dlib image
    dlib::cv_image<dlib::bgr_pixel> dlib_img(frame);

    // Detect faces
    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
    std::vector<dlib::rectangle> faces = detector(dlib_img);

    // Draw landmarks on the faces
    for (const auto& face : faces) {
        dlib::full_object_detection shape = predictor(dlib_img, face);

        // Change color of landmark 0 to red
        int landmarkIndex = 0;  // Change this to the desired landmark index
        cv::Point landmarkPoint(shape.part(landmarkIndex).x(), shape.part(landmarkIndex).y());
        cv::circle(frame, landmarkPoint, 3, cv::Scalar(0, 0, 255), -1);  // Red color

        // Draw landmarks on the image
        for (unsigned int i = 0; i < shape.num_parts(); ++i) {
            if (i != landmarkIndex) {
                cv::circle(frame, cv::Point(shape.part(i).x(), shape.part(i).y()), 3, cv::Scalar(0, 255, 0), -1);
            }
        }
    }

    // Display the image
    cv::imshow("Face Landmark Detection", frame);
    cv::waitKey(0);

    return 0;
}
