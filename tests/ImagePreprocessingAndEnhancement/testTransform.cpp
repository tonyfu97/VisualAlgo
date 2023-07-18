#include "TestHarness.h"
#include "ImagePreprocessingAndEnhancement/Transform.hpp"
#include "helpers/Matrix.hpp"

#include <iostream>
#include <string>
#include <cmath>

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    static void save_image(const std::string &name, const std::string &transform_type)
    {
        Matrix image, transformed_image;
        image.load("datasets/ImagePreprocessingAndEnhancement/" + name + "_resized.ppm");
        if (transform_type == "translate")
        {
            transformed_image = Transform::translate(image, 100, 50);
        }
        else if (transform_type == "scale")
        {
            transformed_image = Transform::scale(image, 2, 0.5, InterpolationType::NEAREST);
        }
        else if (transform_type == "rotate")
        {
            transformed_image = Transform::rotate(image, M_PI / 2);
        }
        else if (transform_type == "shear")
        {
            transformed_image = Transform::shear(image, 0, 0.5);
        }
        else if (transform_type == "perspective")
        {
            Matrix scale_matrix = Transform::scale(0.5, 0.5);
            // change to perspective transform
            scale_matrix.set(2, 0, 0.01);
            scale_matrix.set(2, 1, 0.01);
            transformed_image = Transform::perspective(image, scale_matrix);
        }
        else
        {
            throw std::invalid_argument("Invalid transform type: " + transform_type);
        }
        transformed_image.save("datasets/ImagePreprocessingAndEnhancement/" + name + "_" + transform_type + ".ppm", true);
    }

    TEST(Transform, Translation)
    {
        Matrix image = Matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        Matrix expected = Matrix({{0, 0, 0}, {0, 1, 2}, {0, 4, 5}});
        Matrix actual = Transform::translate(image, 1, 1);
        CHECK(actual.is_close(expected, 0.01));

        image = Matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        expected = Matrix({{0, 0, 0}, {0, 0, 0}, {0, 1, 2}});
        actual = Transform::translate(image, 1, 2, InterpolationType::NEAREST);
        CHECK(actual.is_close(expected, 0.01));

        expected = Matrix({{0, 0, 0}, {1, 2, 3}, {4, 5, 6}});
        actual = Transform::translate(image, 0, 1, InterpolationType::NEAREST);
        CHECK(actual.is_close(expected, 0.01));

        expected = Matrix({{5, 6, 0}, {8, 9, 0}, {0, 0, 0}});
        actual = Transform::translate(image, -1, -1, InterpolationType::NEAREST);
        CHECK(actual.is_close(expected, 0.01));

        save_image("lighthouse", "translate");
    }

    TEST(Transform, Scaling)
    {
        Matrix image = Matrix({{1, 2},
                               {3, 4},
                               {5, 6},
                               {7, 8}});
        Matrix expected = Matrix({{1, 2},
                               {3, 4},
                               {3, 4},
                               {5, 6}});  // shifted down by 1 because of the way the interpolation works (floor)
        Matrix actual = Transform::scale(image, 1, 2, InterpolationType::NEAREST);
        CHECK(actual.is_close(expected, 0.01));

        save_image("lighthouse", "scale");
    }

    TEST(Transform, Rotation)
    {
        Matrix image = Matrix({{1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 9}});
        Matrix expected = Matrix({{7, 4, 1},
                                  {8, 5, 1},
                                  {9, 3, 3}}); // shifted down by 1 because of the way the interpolation works (floor)
        Matrix actual = Transform::rotate(image, M_PI / 2);
        CHECK(actual.is_close(expected, 0.01));

        save_image("lighthouse", "rotate");
    }

    TEST(Transform, Shear)
    {
        Matrix image = Matrix({{1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 9}});
        Matrix expected = Matrix({{4, 2, 0},
                                  {7, 5, 3},
                                  {0, 8, 6}});
        Matrix actual = Transform::shear(image, 0, 1);
        CHECK(actual.is_close(expected, 0.01));

        save_image("lighthouse", "shear");

        bool exception_thrown = false;
        try
        {
            Transform::shear(image, 1, 1);
        }
        catch (const std::invalid_argument &e)
        {
            exception_thrown = true;
        }
        CHECK(exception_thrown);
    }

    TEST(Transform, Perspective)
    {
        

        save_image("lighthouse", "perspective");
    }

}