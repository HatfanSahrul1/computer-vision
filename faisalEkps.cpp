#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/image_io.h>

int main() {
    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
    dlib::shape_predictor sp;
    dlib::deserialize("/home/hatfan/test2/shape_predictor_68_face_landmarks.dat") >> sp;  // Replace with the path to your model

    dlib::array2d<dlib::bgr_pixel> img;
    dlib::load_image(img, "/home/hatfan/test2/facialExp.jpg");  // Replace with the path to your image

    std::vector<dlib::rectangle> faces = detector(img);
    if (!faces.empty()) {
        dlib::full_object_detection shape = sp(img, faces[0]);

        // Use shape to determine facial expression
        // Add your logic here based on landmarks or use a pre-trained model for expression recognition
    }

    return 0;
}
