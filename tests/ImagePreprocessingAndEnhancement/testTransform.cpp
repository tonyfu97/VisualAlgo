#include "TestHarness.h"
#include "ImagePreprocessingAndEnhancement/Transform.hpp"
#include "helpers/Matrix.hpp"

#include <iostream>

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    TEST(Transform, Translation)
    {
        Matrix image = Matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        Matrix expected = Matrix({{0, 0, 0}, {0, 1, 2}, {0, 4, 5}});
        Matrix actual = Transform::translate(image, 1, 1);

        std::cout << "translation: "<< actual << std::endl;

        CHECK(actual == expected);
    }

    TEST(Transform, Scaling)
    {
        Matrix image = Matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        Matrix expected = Matrix({{1, 2, 2}, {4, 5, 6}, {7, 8, 9}});
        Matrix actual = Transform::scale(image, 1, 2);

        std::cout << "scaling: " << actual << std::endl;

        CHECK(actual == expected);
    }

}