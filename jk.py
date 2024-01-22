import cv2
import numpy as np

def draw_bounding_boxes(image, bounding_boxes):
    for box in bounding_boxes:
        cv2.rectangle(image, box[0], box[1], (0, 255, 0), 2)

    cv2.imshow("Bounding Boxes", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def main():
    # Replace "your_image.jpg" with the actual path to your image file
    img = cv2.imread("/home/hatfan/dataset/garis/frame_0.jpg")

    if img is None:
        print("Error: Could not read the image.")
        return

    # Replace "your_annotations.xml" with the actual path to your XML file
    fs = cv2.FileStorage("/home/hatfan/dataset/garis/frame_0.xml", cv2.FILE_STORAGE_READ)

    if not fs.isOpened():
        print("Error: Could not open the XML file.")
        return

    try:
        objects = fs.getNode("annotation")["object"]
        bounding_boxes = []

        for obj in objects:
            box = (
                (int(obj["bndbox"]["xmin"]), int(obj["bndbox"]["ymin"])),
                (int(obj["bndbox"]["xmax"]), int(obj["bndbox"]["ymax"]))
            )
            bounding_boxes.append(box)

        # Draw bounding boxes on the image
        draw_bounding_boxes(img, bounding_boxes)

    except cv2.error as e:
        print(f"OpenCV Exception: {e}")

    fs.release()

if __name__ == "__main__":
    main()
