import cv2
import numpy as np

def detect_balls(image_path):
    # Baca gambar
    image = cv2.imread(image_path, cv2.IMREAD_COLOR)

    # Ubah gambar ke dalam skala abu-abu
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Lakukan deteksi tepi dengan metode Canny
    edges = cv2.Canny(gray, 50, 150, apertureSize=3)

    # Lakukan transformasi Hough Circle untuk mendeteksi lingkaran
    circles = cv2.HoughCircles(
        edges, 
        cv2.HOUGH_GRADIENT, dp=1, minDist=50, param1=50, param2=30, minRadius=10, maxRadius=50
    )

    if circles is not None:
        # Konversi koordinat lingkaran ke dalam format integer
        circles = np.uint16(np.around(circles))

        # Gambar lingkaran yang terdeteksi
        for i in circles[0, :]:
            center = (i[0], i[1])
            radius = i[2]
            
            # Gambar lingkaran pada gambar asli
            cv2.circle(image, center, radius, (0, 255, 0), 2)

        # Tampilkan gambar hasil deteksi
        cv2.imshow('Deteksi Bola', image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    else:
        print("Tidak ada bola yang terdeteksi.")

# Ganti path gambar sesuai dengan lokasi gambar Anda
image_path = '/home/hatfan/test2/bangun.jpg'
detect_balls(image_path)
