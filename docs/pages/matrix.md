# Matrix Class Documentation

The `Matrix` class provides a two-dimensional matrix object, along with numerous methods for performing operations on the matrix.

## Include

``` cpp
#include "helpers/matrix.hpp"
```

## Class Attributes

* `rows` (`int`): The number of rows in the matrix.
* `cols` (`int`): The number of columns in the matrix.
* `data` (`vector<vector<float>>`): A 2D vector that holds the matrix data.

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
