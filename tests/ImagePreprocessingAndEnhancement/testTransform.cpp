#include "TestHarness.h"
#include "ImagePreprocessingAndEnhancement/Transform.hpp"
#include "helpers/Matrix.hpp"

#include <iostream>
#include <string>

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    static void save_image(const std::string &name, const std::string &transform_type, OutputSizeMode sizeMode)
    {
        Matrix image, transformed_image;
        image.load("datasets/ImagePreprocessingAndEnhancement/" + name + "_resized.ppm");
        if (transform_type == "translate")
        {
            transformed_image = Transform::translate(image, 100, 50);
        }
        else if (transform_type == "scale")
        {
            transformed_image = Transform::scale(image, 2, 0.5, InterpolationType::NEAREST, sizeMode);
        }
        else if (transform_type == "rotate")
        {
            transformed_image = Transform::rotate(image, 0.5);
        }
        else if (transform_type == "shear")
        {
            transformed_image = Transform::shear(image, 1, 1);
        }
        else
        {
            throw std::invalid_argument("Invalid transform type: " + transform_type);
        }
        transformed_image.save("datasets/ImagePreprocessingAndEnhancement/" + name + "_" + transform_type + "_" + to_string(sizeMode) + ".ppm", true);
    }

    TEST(Transform, TranslationOriginal)
    {
        Matrix image = Matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        Matrix expected = Matrix({{0, 0, 0}, {0, 1, 2}, {0, 4, 5}});
        Matrix actual = Transform::translate(image, 1, 1);
        CHECK(actual.is_close(expected, 0.01));

        save_image("lighthouse", "translate", OutputSizeMode::Original);
    }

    TEST(Transform, TranslationFit)
    {
        Matrix image = Matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        Matrix expected = Matrix({{0, 0, 0}, {0, 0, 0}, {0, 1, 2}});
        Matrix actual = Transform::translate(image, 1, 2, InterpolationType::NEAREST, OutputSizeMode::Fit);
        CHECK(actual.is_close(expected, 0.01));

        expected = Matrix({{0, 0, 0}, {1, 2, 3}, {4, 5, 6}});
        actual = Transform::translate(image, 0, 1, InterpolationType::NEAREST, OutputSizeMode::Fit);
        CHECK(actual.is_close(expected, 0.01));

        expected = Matrix({{5, 6, 0}, {8, 9, 0}, {0, 0, 0}});
        actual = Transform::translate(image, -1, -1, InterpolationType::NEAREST, OutputSizeMode::Fit);
        CHECK(actual.is_close(expected, 0.01));

        save_image("lighthouse", "translate", OutputSizeMode::Fit);
    }

    TEST(Transform, ScalingExpand)
    {
        Matrix image = Matrix({{1, 2}, {4, 5}});
        Matrix expected = Matrix({{1, 2},
                                  {1, 2},
                                  {1, 2},
                                  {4, 5},
                                  {4, 5},
                                  {4, 5}});
        Matrix actual = Transform::scale(image, 1, 3, InterpolationType::NEAREST, OutputSizeMode::Expand);

        CHECK(actual.is_close(expected, 0.01));

        save_image("lighthouse", "scale", OutputSizeMode::Fit);
    }

}