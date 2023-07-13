# 2. Feature Extraction

## Computer Vision Algorithms

### Sobel Filters (`VisualAlgo::FeatureExtraction::Gradients`)

The `Gradients` class in the `VisualAlgo::FeatureExtraction` namespace is a utility class for computing various gradient measurements of an image. These are important components in many computer vision and image processing tasks such as edge detection and feature extraction. 

The key technique used by this class is the Sobel operator, which is a pair of 3x3 convolution kernels. These kernels are designed to respond maximally to edges running vertically and horizontally relative to the pixel grid, one for each direction (x and y). 

Once the x and y gradients have been computed, it's often useful to also compute the gradient magnitude and direction. The gradient magnitude gives the amount of change at each pixel and the direction gives the orientation of change. 

#### Include

```cpp
#include "FeatureExtraction/Gradients.hpp"
```

#### Static Functions

* `Matrix computeXGradient(const Matrix& image)`: This static function takes an input image in the form of a `Matrix` and computes the x-direction gradients of the image. This operation involves convolving the image with the SobelX kernel that detects changes in intensity in the x-direction. The output is a `Matrix` of the same size as the input image, where each element represents the x-direction gradient at the corresponding pixel in the input image.

* `Matrix computeYGradient(const Matrix& image)`: This static function works similar to `computeXGradient`, but it computes the gradients in the y-direction. The image is convolved with the SobelY kernel. The output is a `Matrix` of the same size as the input image, where each element represents the y-direction gradient at the corresponding pixel in the input image.

* `Matrix computeGradientMagnitude(const Matrix& xGradient, const Matrix& yGradient)`: This static function computes the magnitude of the gradient at each pixel. The gradient magnitude is defined as the square root of the sum of the squares of the x and y gradients. The output is a `Matrix` of the same size as the input gradients, where each element represents the gradient magnitude at the corresponding pixel.

* `Matrix computeGradientDirection(const Matrix& xGradient, const Matrix& yGradient)`: This static function computes the direction of the gradient at each pixel. The gradient direction is defined as the arctangent of the ratio of the y-gradient to the x-gradient. The output is a `Matrix` of the same size as the input gradients, where each element represents the gradient direction at the corresponding pixel.

    The gradient direction is calculated as the arctangent of the ratio of the y-gradient to the x-gradient. In areas of the image where the x-gradient is near zero, the ratio can become very large or very small, leading to potential instability in the arctangent calculation. Unlike the other libraries, I have not addressed this issue yet.

#### Example Usage

In this example, the `Gradients` class is used to compute the x and y gradients of an image, as well as the gradient magnitude and direction. These results are then saved to file and compared with the expected results to ensure the computations are correct.

```cpp
VisualAlgo::Matrix image;
image.load("datasets/FeatureExtraction/lighthouse_resized.ppm");
image.normalize();

VisualAlgo::Matrix image_x_gradient, image_y_gradient, image_gradient_magnitude, image_gradient_direction;
image_x_gradient = VisualAlgo::FeatureExtraction::Gradients::computeXGradient(image);
image_y_gradient = VisualAlgo::FeatureExtraction::Gradients::computeYGradient(image);
image_gradient_magnitude = VisualAlgo::FeatureExtraction::Gradients::computeGradientMagnitude(image_x_gradient, image_y_gradient);
image_gradient_direction = VisualAlgo::FeatureExtraction::Gradients::computeGradientDirection(image_x_gradient, image_y_gradient);

image_x_gradient.save("datasets/FeatureExtraction/lighthouse_x_gradient.ppm", true);
image_y_gradient.save("datasets/FeatureExtraction/lighthouse_y_gradient.ppm", true);
image_gradient_magnitude.save("datasets/FeatureExtraction/lighthouse_gradient_magnitude.ppm", true);
image_gradient_direction.save("datasets/FeatureExtraction/lighthouse_gradient_direction.ppm", true);
```

In this code, `computeXGradient` and `computeYGradient` are used to calculate the x and y gradients of the loaded image respectively. Then `computeGradientMagnitude` and `computeGradientDirection` are used to compute the gradient magnitude and direction respectively. The resulting images are then saved to file for later analysis or visualization.

#### Visual Examples

Below are visual examples of the original image and the computed gradients, gradient magnitude, and gradient direction.

Original Image:

![original_lighthouse](../images/FeatureExtraction/lighthouse_original.png)

X-direction Gradient:

![sobel_x_lighthouse](../images/FeatureExtraction/lighthouse_sobel_x.png)

Y-direction Gradient:

![sobel_y_lighthouse](../images/FeatureExtraction/lighthouse_sobel_y.png)

Gradient Magnitude:

![sobel_mag_lighthouse](../images/FeatureExtraction/lighthouse_sobel_magnitude.png)

Gradient Direction:

![sobel_dir_lighthouse](../images/FeatureExtraction/lighthouse_sobel_direction.png)

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

