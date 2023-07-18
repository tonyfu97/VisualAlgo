# 1. Image Pre-processing and Enhancement

## Computer Vision Algorithms

### Interpolation

The `Interpolate` class in the `VisualAlgo::ImagePreprocessingAndEnhancement` namespace provides different interpolation methods for scaling and enhancing image resolution. Interpolate is a method of estimating values between two points in an image or a series of data points. The `Interpolate` class provides three common types of interpolation: nearest neighbor, bilinear, and bicubic.

![interpolation_illustration](../images/ImagePreprocessingAndEnhancement/interpolation_illustration.jpg)

1. **Nearest Neighbor**: This is the simplest interpolation method where the value of an unknown pixel is assumed to be equal to the value of the nearest pixel in the input image. More precisely, we consider the pixel in the input image that is to the left and/or above (according to the decimal part of the coordinates), in other words, the **floor of the coordinate value** is used to determine the nearest neighbor for interpolation.

2. **Bilinear**: This method takes the weighted average of the four nearest pixels to estimate the value of an unknown pixel. The weights are determined by the distance of the unknown pixel from these known pixels.

3. **Bicubic**: A slightly more sophisticated method. It estimates the value of an unknown pixel by taking the weighted average of the sixteen nearest pixels. The weights are determined by the distance of the unknown pixel from these known pixels and are calculated using a cubic function. 

    Bicubic interpolation uses cubic polynomials to estimate pixel intensities near the pixel of interest \(P(t)\). Particularly, this implementation uses the Catmull-Rom splines, which pass through two control points, \(P_1\) and \(P_2\). These points surround the point of interest, while \(P_0\) and \(P_3\) are used to determine the slope. The Catmull-Rom spline is designed so that the interpolated pixel value is a weighted sum of the four pixels surrounding it. Here's the 1D version with \(t\) representing the point of interest:

    $$P(t) = \sum_{i=0}^{3} P_i Q_i(t)$$

    where \(P_i\) are the control points, and \(Q_i(t)\) are the blending functions for the Catmull-Rom spline:

    $$Q_0(t) = -\frac{1}{2}t^3 + t^2 - \frac{1}{2}t \\
    Q_1(t) = \frac{3}{2}t^3 - 2.5t^2 + 1 \\
    Q_2(t) = -\frac{3}{2}t^3 + 2t^2 + \frac{1}{2}t \\
    Q_3(t) = \frac{1}{2}t^3 - \frac{1}{2}t^2 $$

    Substituting \(Q_i(t)\) into the original equation and simplifying yields:

    $$P(t) = 0.5 \times [ (2 P_1) + (-P_0 + P_2) t + (2P_0 - 5 P_1 + 4 P_2 - P_3) t^2 + (-P_0 + 3 P_1 - 3 P_2 + P_3) t^3 ]$$

    This equation corresponds to the `cubicInterpolation` function in the provided code.

#### Class Members and Methods

- `enum class InterpolationType`: Enumeration that provides a way to select the type of interpolation method. This can be `NEAREST`, `BILINEAR`, or `BICUBIC`.

- `to_string(InterpolationType type)`: A function that takes an `InterpolationType` and returns its string representation.

- `nearest(const Matrix &image, float x, float y)`: A static method that performs nearest neighbor interpolation on the given image at the specified coordinates `(x, y)`.

- `bilinear(const Matrix &image, float x, float y)`: A static method that performs bilinear interpolation on the given image at the specified coordinates `(x, y)`.

- `bicubic(const Matrix &image, float x, float y)`: A static method that performs bicubic interpolation on the given image at the specified coordinates `(x, y)`.

- `interpolate(const Matrix &image, float x, float y, InterpolationType type, float default_value=0.0f)`: A static method that interpolates the given image at the specified coordinates `(x, y)` using the specified interpolation type. If `(x, y)` is outside of the image, then it will return default_value.

- `interpolate(const Matrix &image, float scale, InterpolationType type)`: A static method that scales the given image by the specified scale factor using the specified interpolation type.

- `interpolate(const Matrix &image, int rows, int cols, InterpolationType type)`: A static method that resizes the given image to the specified number of rows and columns using the specified interpolation type.

#### Example Usage

In this example, the `Interpolate` class is used to scale an image using bicubic interpolation.

```cpp
#include "helpers/Matrix.hpp"
#include "ImagePreprocessingAndEnhancement/Interpolate.hpp"

VisualAlgo::Matrix image;
image.load("datasets/ImagePreprocessingAndEnhancement/cat_resized.ppm");

VisualAlgo::Matrix image_scaled = 
    VisualAlgo::ImagePreprocessingAndEnhancement::Interpolate::interpolate(image, 2.0f, 
    VisualAlgo::ImagePreprocessingAndEnhancement::InterpolationType::BICUBIC);

image_scaled.save("datasets/ImagePreprocessingAndEnhancement/cat_scaled.ppm", true);
```

#### Visual Examples

Below are visual examples of the original image and the image after bicubic interpolation.

Original Image:

![original_lighthouse](../images/ImagePreprocessingAndEnhancement/lighthouse_original.png)

Scaled Image (scale = 0.5, method = NEAREST):

![lighthouse_nearest_0.5](../images/ImagePreprocessingAndEnhancement/lighthouse_nearest_0.5.png)

Scaled Image (scale = 0.5, method = BILINEAR):

![lighthouse_bilinear_0.5](../images/ImagePreprocessingAndEnhancement/lighthouse_bilinear_0.5.png)

Scaled Image (scale = 0.5, method = BICUBIC):

![lighthouse_bicubic_0.5](../images/ImagePreprocessingAndEnhancement/lighthouse_bicubic_0.5.png)

#### Note on Image Types:

These interpolation methods are designed to work with grayscale images. Color images are typically represented as multi-channel images (e.g., Red-Green-Blue), and these methods do not directly apply.

#### Note on Simplifications and Differences from Other Libraries:

While these interpolation methods implement the fundamental logic of nearest neighbor, bilinear, and bicubic interpolation, there are several simplifications in the implementation. These include:

1. **Edge Handling**: In the case where an interpolation point falls near the edge or outside the given image, our implementation clamps the coordinates to the image boundary. This approach is straightforward but not always ideal. Other libraries may offer more advanced edge-handling strategies, such as padding, mirroring, or extrapolation.

2. **Optimization**: The bicubic interpolation method, in particular, can be further optimized. Our implementation performs the calculations in a straightforward manner, which could be computationally heavy for large images. Other libraries may use optimized routines or hardware acceleration to speed up these operations.

---

### Transformation

The `Transform` class implements various image transformation operations, each using an associated 3x3 transformation matrix. These operations include translation, scaling, rotation, and shear. 

1. **Translation**: `static Matrix translate(const Matrix &image, int dx, int dy, InterpolationType method = InterpolationType::NEAREST)` Moves an image by `dx` units in the x-direction and `dy` units in the y-direction. The translation matrix is:

    \[
    \begin{pmatrix}
    1 & 0 & dx \\
    0 & 1 & dy \\
    0 & 0 & 1
    \end{pmatrix}
    \]

2. **Scaling**: `static Matrix scale(const Matrix &image, float sx, float sy, InterpolationType method = InterpolationType::NEAREST)` Resizes an image by a factor of `sx` in the x-direction and `sy` in the y-direction. The scaling matrix is:

    \[
    \begin{pmatrix}
    sx & 0 & 0 \\
    0 & sy & 0 \\
    0 & 0 & 1
    \end{pmatrix}
    \]

3. **Rotation**: `static Matrix rotate(const Matrix &image, float angle, InterpolationType method = InterpolationType::NEAREST)` Rotates an image by a specified angle (in radians) in the clockwise direction (because y-axis points down). The rotation matrix is:

    \[
    \begin{pmatrix}
    cos(\theta) & -sin(\theta) & 0 \\
    sin(\theta) & cos(\theta) & 0 \\
    0 & 0 & 1
    \end{pmatrix}
    \]

4. **Shear**: `static Matrix shear(const Matrix &image, float kx, float ky, InterpolationType method = InterpolationType::NEAREST)` Applies a shear transformation with the specified shear factors `kx` and `ky` in the x and y directions respectively. The shear matrix is:

    \[
    \begin{pmatrix}
    1 & kx & 0 \\
    ky & 1 & 0 \\
    0 & 0 & 1
    \end{pmatrix}
    \]

    The shearing factors `kx` and `ky` cannot both be equal to 1. This condition would result in a singular transformation matrix, and the image would collapse into a line.

5. **Affine**: `static Matrix affine(const Matrix &image, const Matrix &transform_matrix, InterpolationType method = InterpolationType::NEAREST)` The above transformations call this method to apply the appropriate transformations. The affine transformation matrix is:

    \[
    \begin{pmatrix}
    a & b & tx \\
    c & d & ty \\
    0 & 0 & 1
    \end{pmatrix}
    \]

    Where `a`, `b`, `c`, and `d` represent scaling, rotation, and shear transformations, and `tx` and `ty` represent translations in the x and y directions, respectively.

6. **Perspective**: `static Matrix perspective(const Matrix &image, const Matrix &transform_matrix, InterpolationType method = InterpolationType::NEAREST)` Perspective transformation is more general than the `affine` transformation due to the presence of non-zero values in the third column of the transformation matrix for perspective transformations. These values (denoted as `h` and `i`) result in a transformation equivalent to shearing along the x and y-axes.

    \[
    \begin{pmatrix}
    a & b & tx \\
    c & d & ty \\
    h & i & 1
    \end{pmatrix}
    \]

#### Example Usage

In this example, we use the `Transform` class to apply various transformations on an image, such as translation, scaling, rotation, shearing, and perspective transformation.

```cpp
#include "TestHarness.h"
#include "ImagePreprocessingAndEnhancement/Transform.hpp"
#include "helpers/Matrix.hpp"

#include <string>
#include <cmath>

VisualAlgo::Matrix image;
image.load("datasets/ImagePreprocessingAndEnhancement/lighthouse_resized.ppm");

// Translate the image
VisualAlgo::Matrix image_translated = 
    VisualAlgo::ImagePreprocessingAndEnhancement::Transform::translate(image, 100, 50);
image_translated.save("datasets/ImagePreprocessingAndEnhancement/lighthouse_translated.ppm", true);

// Scale the image
VisualAlgo::Matrix image_scaled = 
    VisualAlgo::ImagePreprocessingAndEnhancement::Transform::scale(image, 2, 0.5, 
    VisualAlgo::ImagePreprocessingAndEnhancement::InterpolationType::NEAREST);
image_scaled.save("datasets/ImagePreprocessingAndEnhancement/lighthouse_scaled.ppm", true);

// Rotate the image
VisualAlgo::Matrix image_rotated = 
    VisualAlgo::ImagePreprocessingAndEnhancement::Transform::rotate(image, M_PI / 2);
image_rotated.save("datasets/ImagePreprocessingAndEnhancement/lighthouse_rotated.ppm", true);

// Shear the image
VisualAlgo::Matrix image_sheared = 
    VisualAlgo::ImagePreprocessingAndEnhancement::Transform::shear(image, 0, 0.5);
image_sheared.save("datasets/ImagePreprocessingAndEnhancement/lighthouse_sheared.ppm", true);

// Apply perspective transformation on the image
VisualAlgo::Matrix perspective_matrix = VisualAlgo::ImagePreprocessingAndEnhancement::Transform::scale(0.5, 0.5);
perspective_matrix.set(2, 0, 0.01);
perspective_matrix.set(2, 1, 0.01);
VisualAlgo::Matrix image_perspective_transformed = 
    VisualAlgo::ImagePreprocessingAndEnhancement::Transform::perspective(image, perspective_matrix);
image_perspective_transformed.save("datasets/ImagePreprocessingAndEnhancement/lighthouse_perspective.ppm", true);
```

#### Visual Examples

Here are the results from the above code:

1. Translation

    ![lighthouse_translate](../images/ImagePreprocessingAndEnhancement/lighthouse_translate.png)

2. Scaling

    ![lighthouse_scale](../images/ImagePreprocessingAndEnhancement/lighthouse_scale.png)

3. Rotation

    ![lighthouse_rotate](../images/ImagePreprocessingAndEnhancement/lighthouse_rotate.png)

4. Shearing

    ![lighthouse_shear](../images/ImagePreprocessingAndEnhancement/lighthouse_shear.png)

5. Perspective (and scaling)

    ![lighthouse_perspective](../images/ImagePreprocessingAndEnhancement/lighthouse_perspective.png)

---

### Histogram Equalization

The `HistogramEqualization` class in the `VisualAlgo::ImagePreprocessingAndEnhancement` namespace provides a method for improving the contrast in images. Histogram equalization is a method in image processing of contrast adjustment using the image's histogram. This method works by spreading out the most frequent intensity values in an image, resulting in a histogram that better represents all the intensity values. 

#### Class Members and Methods

- `equalize(const Matrix &img)`: A static method that takes an image as a `Matrix` and returns the image after applying histogram equalization.

#### Example Usage

In this example, the `HistogramEqualization` class is used to improve the contrast of an image.

```cpp
#include "helpers/Matrix.hpp"
#include "ImagePreprocessingAndEnhancement/HistogramEqualization.hpp"

VisualAlgo::Matrix image;
image.load("datasets/ImagePreprocessingAndEnhancement/dark_image.ppm");

VisualAlgo::Matrix image_equalized = 
    VisualAlgo::ImagePreprocessingAndEnhancement::HistogramEqualization::equalize(image);

image_equalized.save("datasets/ImagePreprocessingAndEnhancement/dark_image_equalized.ppm", true);
```

#### Visual Examples

Below are visual examples of the original image and the image after histogram equalization.

Original Image (low contrast):

![lighthouse_weak_contrast](../images/ImagePreprocessingAndEnhancement/lighthouse_weak_contrast.png)

Image after Histogram Equalization:

![lighthouse_weak_contrast_equalized](../images/ImagePreprocessingAndEnhancement/lighthouse_weak_contrast_equalized.png)


---

## Neuroscience Models

---
