import sys
import cv2
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtWidgets import QApplication, QLabel, QMainWindow, QVBoxLayout, QWidget

class OpenCVQtApp(QMainWindow):
    def __init__(self):
        super(OpenCVQtApp, self).__init__()

        self.video_capture = cv2.VideoCapture(0)  # Open the default camera (0)

        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)

        self.image_label = QLabel(self.central_widget)
        self.image_label.setAlignment(Qt.AlignCenter)

        self.layout = QVBoxLayout(self.central_widget)
        self.layout.addWidget(self.image_label)

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_frame)
        self.timer.start(100)  # Update every 100 milliseconds

        self.setWindowTitle("OpenCV Qt GUI")
        self.setGeometry(100, 100, 800, 600)

    def update_frame(self):
        ret, frame = self.video_capture.read()

        if ret:
            rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            h, w, ch = rgb_image.shape
            bytes_per_line = ch * w
            q_image = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format_RGB888)
            pixmap = QPixmap.fromImage(q_image)
            self.image_label.setPixmap(pixmap)

    def closeEvent(self, event):
        self.video_capture.release()
        event.accept()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_win = OpenCVQtApp()
    main_win.show()
    sys.exit(app.exec_())
