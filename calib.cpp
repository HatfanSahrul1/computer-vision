#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main() {
    // Baca gambar-gambar chessboard yang digunakan untuk kalibrasi
    std::vector<cv::String> imagePaths;
    cv::glob("*.jpeg", imagePaths);

    // Inisialisasi vektor untuk menyimpan sudut chessboard
    std::vector<std::vector<cv::Point2f>> imagePoints;

    // Inisialisasi ukuran chessboard (jumlah kotak horizontal dan vertikal)
    cv::Size boardSize(9, 6);  // Sesuaikan dengan ukuran chessboard Anda

    // Inisialisasi objek yang akan menyimpan koordinat dunia nyata 3D
    std::vector<std::vector<cv::Point3f>> objectPoints;

    // Inisialisasi vektor untuk menyimpan sudut sudut yang ditemukan
    std::vector<cv::Point2f> corners;
    cv::Mat images = cv::imread("chess.jpeg");

    for (const auto& imagePath : imagePaths) {
        cv::Mat image = cv::imread(imagePath);
        cv::Mat gray;

        // Ubah gambar ke citra grayscale
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

        // Temukan sudut chessboard
        bool found = cv::findChessboardCorners(gray, boardSize, corners);

        if (found) {
            cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1),
                             cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1));
            imagePoints.push_back(corners);

            // Menambahkan koordinat dunia nyata (0,0,0), (1,0,0), (2,0,0), ..., (8,5,0) ke objectPoints
            std::vector<cv::Point3f> obj;
            for (int i = 0; i < boardSize.height; i++) {
                for (int j = 0; j < boardSize.width; j++) {
                    obj.push_back(cv::Point3f(j, i, 0));
                }
            }
            objectPoints.push_back(obj);

            // Gambar sudut chessboard pada citra
            cv::drawChessboardCorners(image, boardSize, corners, found);
            cv::imshow("Chessboard Corners", image);
            cv::waitKey(0);
        }
    }

    // Kalibrasi kamera
    cv::Mat cameraMatrix, distortionCoeffs;
    std::vector<cv::Mat> rvecs, tvecs;
    cv::calibrateCamera(objectPoints, imagePoints, images.size(), cameraMatrix, distortionCoeffs, rvecs, tvecs);


    //cv::FileStorage fs("camera_parameters.yml", cv::FileStorage::WRITE);
    //
    // Tampilkan parameter instrinsik
    std::cout << "Camera Matrix:" << std::endl << cameraMatrix << std::endl;
    std::cout << "Distortion Coefficients:" << std::endl << distortionCoeffs << std::endl;

    return 0;
}