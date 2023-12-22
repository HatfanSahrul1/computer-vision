import cv2
import numpy as np
import os

# Open the camera
vcap = cv2.VideoCapture(0)

if not vcap.isOpened():
    print("Error opening camera.")
    exit()

# Set the desired window size
window_width = 640  # Set your desired width
window_height = int(window_width * 9 / 16)  # Maintain the 16:9 aspect ratio

# Create a named window
cv2.namedWindow("Output Window", cv2.WINDOW_NORMAL)

# Resize the window
cv2.resizeWindow("Output Window", window_width, window_height)

is_not_playing = False

while True:
    ret, frame = vcap.read()

    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Blur the image to reduce noise and improve circle detection
    gray_blur = cv2.GaussianBlur(gray, (9, 9), 2, 2)

    # Use Hough Circle detection to find circles (balls) in the image
    circles = cv2.HoughCircles(
        gray_blur, cv2.HOUGH_GRADIENT, 1, gray_blur.shape[0] // 8, param1=100, param2=30, minRadius=10, maxRadius=50
    )

    # Draw detected circles on the frame
    if circles is not None:
        circles = np.uint16(np.around(circles))
        for circle in circles[0, :]:
            center = (circle[0], circle[1])
            radius = circle[2]
            cv2.circle(frame, center, radius, (0, 255, 0), 2)

        # Display the number of balls detected
        text = "Balls detected: {}".format(circles.shape[1])
        cv2.putText(frame, text, (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0), 2)

        # Play a sound when a ball is detected
        #if circles.shape[1] >= 1:
        #    if not is_not_playing:
        #        os.system("canberra-gtk-play -f /home/hatfan/test2/mix.wav")
        #    is_not_playing = True
        #    cv2.waitKey(1)
        #else:
         #   is_not_playing = False

    # Perform edge detection
    edges = cv2.Canny(gray_blur, 50, 150)

    # Use Hough Line Transform to detect goal posts
    lines = cv2.HoughLines(edges, 1, np.pi / 180, threshold=100)

    # Draw detected lines on the frame
    if lines is not None:
        for line in lines:
            rho, theta = line[0]
            a = np.cos(theta)
            b = np.sin(theta)
            x0 = a * rho
            y0 = b * rho
            x1 = int(x0 + 1000 * (-b))
            y1 = int(y0 + 1000 * (a))
            x2 = int(x0 - 1000 * (-b))
            y2 = int(y0 - 1000 * (a))
            cv2.line(frame, (x1, y1), (x2, y2), (0, 0, 255), 2)

    # Display the frame
    cv2.imshow("Output Window", frame)

    # Exit when the 'Esc' key is pressed
    if cv2.waitKey(1) == 27:
        break

# Release the camera
vcap.release()
cv2.destroyAllWindows()
