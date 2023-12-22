import cv2
import xml.etree.ElementTree as ET

def draw_bounding_boxes(image_path, annotations_path):
    # Load the image
    img = cv2.imread(image_path)

    # Parse the XML file with annotations
    tree = ET.parse(annotations_path)
    root = tree.getroot()

    # Iterate over all objects in the XML file
    for obj in root.findall('object'):
        object_name = obj.find('name').text
        xmin = int(obj.find('bndbox/xmin').text)
        ymin = int(obj.find('bndbox/ymin').text)
        xmax = int(obj.find('bndbox/xmax').text)
        ymax = int(obj.find('bndbox/ymax').text)

        # Draw a bounding box on the image
        cv2.rectangle(img, (xmin, ymin), (xmax, ymax), (0, 255, 0), 2)
        cv2.putText(img, object_name, (xmin, ymin - 5), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

    # Display the image with bounding boxes
    cv2.imshow('Object Detection', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

# Replace with the actual paths to your image and XML annotations
image_path = '/home/hatfan/test2/kuncitest.jpg'
annotations_path = '/home/hatfan/test2/kursi.xml'

# Call the function to draw bounding boxes on the image
draw_bounding_boxes(image_path, annotations_path)
