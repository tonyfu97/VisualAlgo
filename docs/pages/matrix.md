# VisualAlgo::Matrix Struct Documentation

The `Matrix` struct provides a two-dimensional matrix object, along with numerous methods for performing operations on the matrix.

---

## Include

``` cpp
#include "helpers/matrix.hpp"
```
---

## Struct Attributes

* `rows` (`int`): The number of rows in the matrix.
* `cols` (`int`): The number of columns in the matrix.
* `data` (`vector<vector<float>>`): A 2D vector that holds the matrix data.

---

## Constructors

* `Matrix(int rows, int cols)`: Constructs a new `Matrix` object with the given number of rows and columns. The matrix is initialized with all elements set to 0.

```cpp
VisualAlgo::Matrix m(3, 4); // Creates a 3x4 matrix with all elements initialized to 0
```

* `Matrix(int rows, int cols, float value)`: Constructs a new `Matrix` object with the given number of rows and columns. The matrix is initialized with all elements set to the provided value.

```cpp
VisualAlgo::Matrix m(3, 4, 1.0); // Creates a 3x4 matrix with all elements initialized to 1.0
```

* `Matrix(vector<vector<float>> data)`: Constructs a new `Matrix` object with the provided 2D vector data.

```cpp
std::vector<std::vector<float>> data = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
VisualAlgo::Matrix m(data); // Creates a 2x3 matrix with the provided data
```

or 

```cpp
VisualAlgo::Matrix m({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}});
```

* `Matrix(const Matrix &other)`: Copy constructor. Constructs a new `Matrix` object that is a copy of the provided matrix.

```cpp
VisualAlgo::Matrix m1(3, 4, 1.0);
VisualAlgo::Matrix m2(m1); // Creates a new matrix that is a copy of m1
```

---

## Special Matrix Constructors

* `Matrix::zeros(int rows, int cols)`: Returns a new `Matrix` object with the specified number of rows and columns. All elements of the matrix are initialized to 0.

```cpp
VisualAlgo::Matrix m = VisualAlgo::Matrix::zeros(3, 4); // Creates a 3x4 matrix with all elements initialized to 0
```

* `Matrix::ones(int rows, int cols)`: Returns a new `Matrix` object with the specified number of rows and columns. All elements of the matrix are initialized to 1.

```cpp
VisualAlgo::Matrix m = VisualAlgo::Matrix::ones(3, 4); // Creates a 3x4 matrix with all elements initialized to 1
```

* `Matrix::eye(int rows, int cols)`: Returns a new identity `Matrix` object with the specified number of rows and columns. All diagonal elements are set to 1, and all other elements are set to 0.

```cpp
VisualAlgo::Matrix m = VisualAlgo::Matrix::eye(3, 3); // Creates a 3x3 identity matrix
```

---

## Random Matrix Constructors

* `Matrix::random(int rows, int cols)`: Returns a new `Matrix` object with the specified number of rows and columns. All elements of the matrix are initialized to a random floating point value in the range [0, 1].

```cpp
VisualAlgo::Matrix m = VisualAlgo::Matrix::random(3, 4); // Creates a 3x4 matrix with all elements initialized to a random value
```

* `Matrix::random(int rows, int cols, float min, float max)`: Returns a new `Matrix` object with the specified number of rows and columns. All elements of the matrix are initialized to a random floating point value in the range [min, max].

```cpp
VisualAlgo::Matrix m = VisualAlgo::Matrix::random(3, 4, -1.0, 1.0); // Creates a 3x4 matrix with all elements initialized to a random value between -1.0 and 1.0
```

---

## Element-wise Operations

Element-wise operations perform the operation on each element of the matrix independently.

* `Matrix &operator=(const Matrix &other)`: Assignment operator. Copies the provided matrix to the current matrix.

```cpp
VisualAlgo::Matrix m1(3, 4, 1.0);
VisualAlgo::Matrix m2 = m1; // m2 is now a copy of m1
```

* `Matrix operator+(const Matrix &other)`: Adds the provided matrix to the current matrix.

```cpp
VisualAlgo::Matrix m1(2, 2, 1.0);
VisualAlgo::Matrix m2(2, 2, 2.0);
VisualAlgo::Matrix m3 = m1 + m2; // m3 is now a 2x2 matrix with all elements set to 3.0
```

* ` Matrix operator+(const float &other)`: Add the provided float to all entries.

Also support other common arithmetic operators.

---

## Element-wise Comparison Functions

* `Matrix::elementwise_max(const Matrix &a, const Matrix &b)`: Returns a new `Matrix` that is the element-wise maximum of matrices `a` and `b`. The dimensions of `a` and `b` must be the same.

```cpp
VisualAlgo::Matrix a = VisualAlgo::Matrix::ones(3, 4);
VisualAlgo::Matrix b = VisualAlgo::Matrix::zeros(3, 4);
VisualAlgo::Matrix m = VisualAlgo::Matrix::elementwise_max(a, b); // m will be a 3x4 matrix with all elements equal to 1
```

* `Matrix::elementwise_min(const Matrix &a, const Matrix &b)`: Returns a new `Matrix` that is the element-wise minimum of matrices `a` and `b`. The dimensions of `a` and `b` must be the same.

```cpp
VisualAlgo::Matrix a = VisualAlgo::Matrix::ones(3, 4);
VisualAlgo::Matrix b = VisualAlgo::Matrix::zeros(3, 4);
VisualAlgo::Matrix m = VisualAlgo::Matrix::elementwise_min(a, b); // m will be a 3x4 matrix with all elements equal to 0
```

The `Matrix` struct supports a variety of comparison operations for comparing two `Matrix` objects or a `Matrix` object with a float.

* `bool operator==(const Matrix &other) const`: Compares the current matrix with `other` for equality. Returns `true` if all elements in the two matrices are exactly equal, and `false` otherwise.

```cpp
Matrix m1({{1, 2, 3}, {4, 5, 6}});
Matrix m2({{1, 2, 3}, {4, 5, 6}});
bool isEqual = (m1 == m2); // Returns true
```

* `bool operator!=(const Matrix &other) const`: Compares the current matrix with `other` for inequality. Returns `true` if any element in the two matrices is not equal, and `false` otherwise.

```cpp
Matrix m1({{1, 2, 3}, {4, 5, 6}});
Matrix m2({{1, 2, 3}, {7, 8, 9}});
bool isNotEqual = (m1 != m2); // Returns true
```

* `bool is_close(const Matrix &other, float tolerance=1e-5) const`: Compares the current matrix with `other` within a given `tolerance`. Returns `true` if the absolute difference between each corresponding pair of elements in the two matrices is less than or equal to the `tolerance`, and `false` otherwise.

```cpp
Matrix m1({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}});
Matrix m2({{1.00001, 2.00001, 3.00001}, {3.99999, 5.00001, 5.99999}});
bool isClose = m1.is_close(m2); // Returns true
```

* `Matrix operator>(const Matrix &other) const`: Returns a binary matrix with `1`s where the corresponding element in the current matrix is greater than that in `other`, and `0`s elsewhere.

```cpp
Matrix m1({{1, 2, 3}, {4, 5, 6}});
Matrix m2({{-1, 2, 4}, {-99, 55, 0}});
Matrix m3 = m1 > m2; // Returns a binary matrix
```

* `Matrix operator<(const Matrix &other) const`: Similar to the `>` operator, but checks for less than.

* `Matrix operator>=(const Matrix &other) const`: Similar to the `>` operator, but checks for greater than or equal to.

* `Matrix operator<=(const Matrix &other) const`: Similar to the `>` operator, but checks for less than or equal to.

In addition to the matrix-matrix comparison operators, there are similar matrix-float comparison operators for comparing each element in a matrix to a float. These are `operator>(const float &other) const`, `operator<(const float &other) const`, `operator>=(const float &other) const`, and `operator<=(const float &other) const`.

```cpp
Matrix m1({{1, 2, 3}, {4, 5, 6}});
Matrix m2 = m1 > 3; // Returns a binary matrix with `1`s where the elements in m1 are greater than 3 and `0`s elsewhere
```

---

## Matrix Operations

* `Matrix transpose()`: Returns the transpose of the current matrix.

```cpp
VisualAlgo::Matrix m1(2, 3, 1.0);
VisualAlgo::Matrix m2 = m1.transpose(); // m2 is now a 3x2 matrix
```

* `float dot(const Matrix &other)`: Calculates the dot product of the current matrix with the provided matrix.

```cpp
VisualAlgo::Matrix m1(3, 3, 1.0);
VisualAlgo::Matrix m2(3, 3, 2.0);
float result = m1.dot(m2); // result is now 18
```

* `Matrix Matrix::matmul(const Matrix &other)`: Matrix multiplication.

```cpp
auto m1 = Matrix({{1, 2, 3}, {4, 5, 6}});
auto m2 = Matrix({{10, 11}, {20, 21}, {30, 31}});
auto m3 = m1.matmul(m2);
```

---

## Accessors

* `void set(int row, int col, float value)`: Sets the value at the specified row and column in the matrix.

```cpp
VisualAlgo::Matrix m(3, 4, 0.0);
m.set(1, 2, 1.0); // Sets the value at row 1, column 2 to 1.0
```

* `const float get(int row, int col) const`: Returns the value at the specified row and column in the matrix.

```cpp
VisualAlgo::Matrix m(3, 4, 1.0);
float value = m.get(2, 3); // Gets the value at row 2, column 3
```

* `std::vector<float> &operator[](int row)`: Returns the row at the specified index in the matrix.

```cpp
VisualAlgo::Matrix m(3, 4, 1.0);
std::vector<float> row = m[1]; // Gets the second row of the matrix
```

---

## Statistics

* `float sum()`: Returns the sum of all elements in the matrix.

```cpp
VisualAlgo::Matrix m(2, 3, 1.0);
float sum = m.sum(); // sum is now 6.0
```

* `float mean()`: Returns the mean (average) of all elements in the matrix.

```cpp
VisualAlgo::Matrix m(2, 3, 1.0);
float mean = m.mean(); // mean is now 1.0
```

Also supports `std()`, `max()`, and `min()` operations.

---

## Image Operations

* `void Matrix::load(const std::string &filename)`: This function loads an image from the specified file path and stores it as a grayscale matrix. The function can only handle images in PPM format (P6). If the file doesn't exist or the file format is not P6, it will throw a runtime error.

```cpp
VisualAlgo::Matrix m;
m.load("path_to_your_image.ppm"); // Loads the image from the specified path
```
This function reads the image file as a binary file. It first reads the header to ensure that the image is in the correct format (P6), then reads the width and height of the image. The pixel data is then read and converted from RGB to grayscale using the ITU-R BT.709 luma transform. The grayscale pixel values are stored in the `data` member of the `Matrix` object.

* `Matrix Matrix::load(const std::string &filename, int rows, int cols)`: Directly load an image.

```cpp
VisualAlgo::Matrix m = VisualAlgo::Matrix.load("path_to_your_image.ppm", 256, 256);
```

* `void Matrix::save(const std::string &filename, bool normalize) const`: This function saves the matrix as an image to the specified file path. The image is saved in PPM format (P6). The `normalize` parameter specifies whether the matrix data should be normalized to the range 0-255 before saving. If not normalized and the pixel values are not within this range, a runtime error is thrown.

```cpp
VisualAlgo::Matrix m(3, 4, 1.0);
m.save("path_to_save_image.ppm", true); // Normalizes and saves the matrix as an image to the specified path
```
This function first checks if the data needs normalization based on the `normalize` flag. If true, it normalizes the data in the `Matrix` object to the range 0-255 using the `normalize255()` function. Then it writes the image data to the file in PPM format (P6). The pixel data is written as RGB, where the R, G, and B values are all equal, resulting in a grayscale image.

* `void Matrix::normalize()`: This function normalizes the values in the matrix to the range [0, 1].

```cpp
VisualAlgo::Matrix m(3, 4, 1.0);
m.normalize(); // Normalizes the matrix values to the range [0, 1.0]
```

* `void Matrix::normalize255()`: This function normalizes the values in the matrix to the range [0.0, 255.0]. This is useful to prepare the data for saving as an image, since pixel values in an image must be in this range.

```cpp
VisualAlgo::Matrix m(3, 4, 1.0);
m.normalize255(); // Normalizes the matrix values to the range [0, 255.0]
```
* `void Matrix::relu()`: This function applies the ReLU (Rectified Linear Unit) operation to the matrix. It replaces all negative pixel values with zeros, effectively achieving half-wave rectification.

```cpp
VisualAlgo::Matrix m(3, 4, -1.0);
m.relu(); // Changes all negative values to 0
```

* `void abs()`: This function take the absolute value of all the entries.

* `Matrix Matrix::cross_correlate(const VisualAlgo::Matrix &kernel, int padding, int stride) const`: This function performs the cross-correlation operation between the matrix and the provided kernel. The padding and stride parameters control the operation. If the kernel size is larger than the matrix or the stride is less than or equal to zero, or padding is negative, it will throw an invalid_argument exception.

```cpp
VisualAlgo::Matrix m(3, 4, 1.0);
VisualAlgo::Matrix kernel(2, 2, 0.5);
VisualAlgo::Matrix result = m.cross_correlate(kernel, 1, 2); // Perform cross-correlation
```
This function creates an output matrix of appropriate size based on the input matrix, kernel, padding, and stride. It then performs the cross-correlation operation and stores the result in the output matrix.

* `Matrix Matrix::cross_correlate(const VisualAlgo::Matrix &kernel) const`: This function performs cross-correlation on the matrix with the provided kernel. The output matrix is always the same size as the input matrix. This operation effectively considers there to be zero padding beyond the edges of the original matrix and will wrap around when indexing beyond its dimensions.

* `Matrix Matrix::cross_correlate_full(const VisualAlgo::Matrix &kernel) const`: This function performs cross-correlation operation on the matrix with the provided kernel, with zero padding. The output matrix size is larger than the input matrix size, taking into account the kernel size and the full overlap.

* `Matrix Matrix::flip() const`: This function returns a new matrix which is the flipped version of the current matrix. This is particularly useful when trying to perform convolution using a kernel, as convolution is mathematically the same as cross-correlation with a flipped kernel.

* `Matrix Matrix::convolve(const VisualAlgo::Matrix &kernel, int padding, int stride) const`: This function performs convolution between the matrix and the provided kernel. It first flips the kernel and then performs cross-correlation. The padding and stride parameters are similar to the cross-correlation function.

* `Matrix Matrix::convolve(const VisualAlgo::Matrix &kernel) const`: This function performs convolution on the matrix with the provided kernel and keeps the same size. This operation effectively considers there to be zero padding beyond the edges of the original matrix and will wrap around when indexing beyond its dimensions.
