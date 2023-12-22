import tensorflow as tf
from tensorflow.keras.preprocessing import image
from tensorflow.keras.applications import VGG16
from tensorflow.keras.applications.vgg16 import preprocess_input, decode_predictions
import numpy as np

# Load a pre-trained VGG16 model
base_model = VGG16(weights='imagenet')

# Replace this with the path to your image
image_path = '/home/hatfan/test2/try.jpg'

# Load and preprocess the image
img = image.load_img(image_path, target_size=(224, 224))
img_array = image.img_to_array(img)
img_array = np.expand_dims(img_array, axis=0)
img_array = preprocess_input(img_array)

# Get model predictions
predictions = base_model.predict(img_array)

# Decode predictions and print top results
decoded_predictions = decode_predictions(predictions)
print(decoded_predictions)
