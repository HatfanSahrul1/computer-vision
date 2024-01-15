import cv2

video_stream_address = "https://10.252.133.72:8080/videofeed?something.mjpeg"

# Open the video stream and make sure it's opened
vcap = cv2.VideoCapture(video_stream_address)

if not vcap.isOpened():
    print("Error opening video stream or file")
    exit(-1)

# Set the desired window size (fullscreen)
cv2.namedWindow("Output Window", cv2.WINDOW_NORMAL)
cv2.setWindowProperty("Output Window", cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)

while True:
    ret, frame = vcap.read()

    # Display the frame
    cv2.imshow("Output Window", frame)

    if cv2.waitKey(1) == 27:  # Exit when the 'Esc' key is pressed
        break

vcap.release()
cv2.destroyAllWindows()
