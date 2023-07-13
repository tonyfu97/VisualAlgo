# 2. Feature Extraction

## Computer Vision Algorithms

### Sobel Filters (`VisualAlgo::FeatureExtraction::Gradients`)

The `Gradients` class in the `VisualAlgo::FeatureExtraction` namespace is a utility class for computing the x and y gradients of an image, which are important components in various computer vision and image processing tasks such as edge detection and feature extraction. 

The key technique used by this class is the Sobel operator, which is a pair of 3x3 convolution kernels. These kernels are designed to respond maximally to edges running vertically and horizontally relative to the pixel grid.

The x-direction kernel is as follows:

$$
Sobel_x = 
\begin{bmatrix}
1 & 0 & -1 \\
2 & 0 & -2 \\
1 & 0 & -1
\end{bmatrix}
$$

The y-direction kernel is as follows:

$$
Sobel_y = 
\begin{bmatrix}
1 & 2 & 1 \\
0 & 0 & 0 \\
-1 & -2 & -1
\end{bmatrix}
$$

#### Include

```cpp
#include "FeatureExtraction/Gradients.hpp"
```

#### Static Functions

* `Matrix computeXGradient(const Matrix& image)`: This static function takes an input image in the form of a `Matrix` and computes the x-direction gradients of the image. This operation involves convolving the image with the SobelX kernel that detects changes in intensity in the x-direction. The output is a `Matrix` of the same size as the input image, where each element represents the x-direction gradient at the corresponding pixel in the input image.

* `Matrix computeYGradient(const Matrix& image)`: This static function works similar to `computeXGradient`, but it computes the gradients in the y-direction. The image is convolved with the SobelY kernel. The output is a `Matrix` of the same size as the input image, where each element represents the y-direction gradient at the corresponding pixel in the input image.

#### Example Usage

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

#### Visual Examples

Below are visual examples of the original image and the computed gradients.

Original Image:

![original_lighthouse](../images/FeatureExtraction/lighthouse_original.png)

X-direction Gradient:

![sobel_x_lighthouse](../images/FeatureExtraction/lighthouse_sobel_x.png)

Y-direction Gradient:

![sobel_y_lighthouse](../images/FeatureExtraction/lighthouse_sobel_y.png)

---

### Non-Max Suppression

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

