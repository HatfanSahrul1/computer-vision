import numpy as np
import onnx
from spox import argument, build, inline, Tensor

# Define input shapes based on the expected input of your models
input_shape = (1, 3, 320, 320)

# Create input tensors with the correct shape and data type
a = argument(Tensor(np.float32, input_shape))
b = argument(Tensor(np.float32, (1,)))

# Load the remade models
model1 = onnx.load("/home/hatfan/test2/models/L-normal.onnx")
model2 = onnx.load("/home/hatfan/test2/models/Goal-normal.onnx")

# Inline the models and forward the arguments
# Also unwrap all the results - assuming there's just one
(r1,) = inline(model1)(a, b).values()
(r2,) = inline(model2)(a, b).values()

# Take the arithmetic mean
r = (r1 + r2) / 2.0

# Build the composed model with given model inputs and outputs (with names)
model = build({'images': a, 'metadata': b}, {'result': r})
onnx.save(model, "composed_model.onnx")
