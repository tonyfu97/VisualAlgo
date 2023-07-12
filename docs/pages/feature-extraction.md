# 2. Feature Extraction

## Computer Vision Algorithms

### `VisualAlgo::FeatureExtraction::Gradients` Class Documentation

The `Gradients` class in the `VisualAlgo::FeatureExtraction` namespace is a utility class for computing the x and y gradients of an image, which are important components in various computer vision and image processing tasks such as edge detection and feature extraction.

#### Include

```cpp
#include "FeatureExtraction/Gradients.hpp"
```

#### Static Functions

* `Matrix computeXGradient(const Matrix& image)`: This static function takes an input image in the form of a `Matrix` and computes the x-direction gradients of the image. This operation typically involves convolving the image with a kernel (e.g., the Sobel operator in the x-direction) that detects changes in intensity in the x-direction. The output is a `Matrix` of the same size as the input image, where each element represents the x-direction gradient at the corresponding pixel in the input image.

* `Matrix computeYGradient(const Matrix& image)`: This static function works similar to `computeXGradient`, but it computes the gradients in the y-direction. The output is a `Matrix` of the same size as the input image, where each element represents the y-direction gradient at the corresponding pixel in the input image.

## Example Usage

In this example, the `Gradients` class is used to compute the x and y gradients of an image. These gradients are then saved to file and compared with the expected gradients to ensure the computations are correct.

```cpp
VisualAlgo::Matrix image;
image.load("datasets/FeatureExtraction/cat_resized.ppm");
image.normalize();

VisualAlgo::Matrix image_x_gradient, image_y_gradient;
image_x_gradient = VisualAlgo::FeatureExtraction::Gradients::computeXGradient(image);
image_y_gradient = VisualAlgo::FeatureExtraction::Gradients::computeYGradient(image);

image_x_gradient.save("datasets/FeatureExtraction/cat_x_gradient.ppm", true);
image_y_gradient.save("datasets/FeatureExtraction/cat_y_gradient.ppm", true);
```

In this code, `computeXGradient` and `computeYGradient` are used to calculate the x and y gradients of the loaded image respectively. The resulting gradient images are then saved to file for later analysis or visualization.

---

### Canny Edge Detection

---

### Corner Detection

---

### Blob Detection

---

### SIFT

---

### SURF

---

### ORB

---

### HOG

---


## Neuroscience Models

### Simple and Complex Cell Models

---

