import xml.etree.ElementTree as ET

# Assuming you have predictions from your object detection model
predictions = [
    {'filename': 'key1.jpg', 'object_name': 'key', 'xmin': 10, 'ymin': 20, 'xmax': 50, 'ymax': 70},
    # Add more predictions as needed
]

# Create an XML file for predictions
root = ET.Element("annotation")

for pred in predictions:
    obj_elem = ET.SubElement(root, "object")
    ET.SubElement(obj_elem, "name").text = pred['object_name']

    bndbox_elem = ET.SubElement(obj_elem, "bndbox")
    ET.SubElement(bndbox_elem, "xmin").text = str(pred['xmin'])
    ET.SubElement(bndbox_elem, "ymin").text = str(pred['ymin'])
    ET.SubElement(bndbox_elem, "xmax").text = str(pred['xmax'])
    ET.SubElement(bndbox_elem, "ymax").text = str(pred['ymax'])

tree = ET.ElementTree(root)
tree.write("/home/hatfan/test2/kursi.xml")

# Now, you can use your XML parsing code to extract information from the predictions XML file.
