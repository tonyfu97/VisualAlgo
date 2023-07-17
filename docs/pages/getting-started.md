# Getting Started

## Prerequisites

You will need a compiler that supports C++17 to build and run this project. No external libraries are required at this moment.

## Instructions

Follow these steps to get a copy of the project and build the library on your local machine:

1. Clone the project to your local machine:
```
git clone git@github.com:tonyfu97/VisualAlgo.git
```

2. Navigate to the project directory:
```
cd VisualAlgo
```

3. Compile the project to generate the library:
```
make
```

The command will create a file named `libVisualAlgo.a` in the project directory. This is a static library that can be linked to your C++ projects. 

To use the `libVisualAlgo.a` library in your C++ code, include the necessary header files in your source code. When compiling your code, link against `libVisualAlgo.a`.

Here is an example of how to do this:

```cpp
#include "path_to_VisualAlgo/Interpolate.hpp"
#include "path_to_VisualAlgo/Transform.hpp"
// other includes as needed
```

And an example compilation command might look like this:

```
g++ -std=c++17 your_code.cpp -L. -lVisualAlgo -o your_program
```

## Documentation

The detailed documentation of each class and method is provided in the source code. Here is the documentation link for the `Matrix` class: [Matrix documentation](matrix.md)

## Note

Please be aware that this library currently supports only grayscale images. All algorithms and methods have been unit tested against "ground-truth" images generated with Python's CV libraries such as Skimage. Despite testing, there might still be bugs. If you discover any bugs or have suggestions for improvements, feel free to raise an issue or submit a pull request.
