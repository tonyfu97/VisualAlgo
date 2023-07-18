#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "ImagePreprocessingAndEnhancement/Interpolate.hpp"
#include "test_utils.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>

const float MAX_PROPORTION_ABS_DIFF = 0.1f;
// The test conditions are made lenient due to the inherent differences in interpolation methods. The ground-truth images are generated using the scipy.ndimage.zoom function, which uses a different interpolation approach.

std::string to_string_with_precision(const float value, const int n = 1)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(n) << value;
    return out.str();
}

static bool test_interpolation(std::string img_name, float scale, VisualAlgo::ImagePreprocessingAndEnhancement::InterpolationType type)
{
    VisualAlgo::Matrix image, image_interpolated_expected;
    image.load("datasets/ImagePreprocessingAndEnhancement/" + img_name + "_resized.ppm");
    image_interpolated_expected.load("datasets/ImagePreprocessingAndEnhancement/" + img_name + "_expected_" + to_string(type) + "_" + to_string_with_precision(scale) + ".ppm");

    image.normalize();
    image_interpolated_expected.normalize();

    VisualAlgo::Matrix image_interpolated = VisualAlgo::ImagePreprocessingAndEnhancement::Interpolate::interpolate(image, scale, type);

    image_interpolated.save("datasets/ImagePreprocessingAndEnhancement/" + img_name + "_interpolated_" + to_string(type) + "_" + to_string_with_precision(scale) + ".ppm", true);

    float padet = proportionAbsDiffExceedTol(image_interpolated, image_interpolated_expected, 0.1);

    // std::cout << "Proportion of absolute difference exceeding tolerance for " << img_name << "_interpolated.ppm: " << padet << std::endl;

    return (padet < MAX_PROPORTION_ABS_DIFF);
}

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{
    TEST(InterpolationTestSuite, InterpolationCatUpsize)
    {
        CHECK(test_interpolation("cat", 2.0, InterpolationType::NEAREST));
        CHECK(test_interpolation("cat", 2.0, InterpolationType::BILINEAR));
        // CHECK(test_interpolation("cat", 2.0, InterpolationType::BICUBIC));
    }

    TEST(InterpolationTestSuite, InterpolationCatDownsize)
    {
        CHECK(test_interpolation("cat", 0.5, InterpolationType::NEAREST));
        CHECK(test_interpolation("cat", 0.5, InterpolationType::BILINEAR));
        // CHECK(test_interpolation("cat", 0.5, InterpolationType::BICUBIC));
    }

    TEST(InterpolationTestSuite, InterpolationLighthouseUpsize)
    {
        CHECK(test_interpolation("lighthouse", 2.0, InterpolationType::NEAREST));
        CHECK(test_interpolation("lighthouse", 2.0, InterpolationType::BILINEAR));
        // CHECK(test_interpolation("lighthouse", 2.0, InterpolationType::BICUBIC));
    }

    TEST(InterpolationTestSuite, InterpolationLighthouseDownsize)
    {
        CHECK(test_interpolation("lighthouse", 0.5, InterpolationType::NEAREST));
        CHECK(test_interpolation("lighthouse", 0.5, InterpolationType::BILINEAR));
        // CHECK(test_interpolation("lighthouse", 0.5, InterpolationType::BICUBIC));
    }

    TEST(InterpolationTestSuite, InterpolationMondrianUpsize)
    {
        CHECK(test_interpolation("mondrian", 2.0, InterpolationType::NEAREST));
        CHECK(test_interpolation("mondrian", 2.0, InterpolationType::BILINEAR));
        // CHECK(test_interpolation("mondrian", 2.0, InterpolationType::BICUBIC));
    }

    TEST(InterpolationTestSuite, InterpolationMondrianDownsize)
    {
        CHECK(test_interpolation("mondrian", 0.5, InterpolationType::NEAREST));
        CHECK(test_interpolation("mondrian", 0.5, InterpolationType::BILINEAR));
        // CHECK(test_interpolation("mondrian", 0.5, InterpolationType::BICUBIC));
    }

    TEST(InterpolationTestSuite, NearestInterpolateMatrix)
    {
        Matrix m1 = Matrix({{1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9}});
        CHECK_EQUAL(1, Interpolate::nearest(m1, 0, 0.4));
        CHECK_EQUAL(1, Interpolate::nearest(m1, 0.4, 0.4));
        CHECK_EQUAL(2, Interpolate::nearest(m1, 1.6, 0.4));
        CHECK_EQUAL(3, Interpolate::nearest(m1, 2.6, 0.4));
        CHECK_EQUAL(4, Interpolate::nearest(m1, 0.4, 1.6));
        CHECK_EQUAL(5, Interpolate::nearest(m1, 1.6, 1.6));
        CHECK_EQUAL(6, Interpolate::nearest(m1, 2.6, 1.6));
        CHECK_EQUAL(7, Interpolate::nearest(m1, 0.4, 2.6));
        CHECK_EQUAL(8, Interpolate::nearest(m1, 1.6, 2.6));
        CHECK_EQUAL(9, Interpolate::nearest(m1, 2.6, 2.6));

        Matrix m2 = Matrix({{1, 2},
                            {4, 5},
                            {7, 8}});
        Matrix m2i_actual = Interpolate::interpolate(m2, 2, InterpolationType::NEAREST);
        Matrix m2i_expected = Matrix({{1, 1, 2, 2},
                                      {1, 1, 2, 2},
                                      {4, 4, 5, 5},
                                      {4, 4, 5, 5},
                                      {7, 7, 8, 8},
                                      {7, 7, 8, 8}});
        CHECK(m2i_actual.is_close(m2i_expected, 0.01));
    }

    TEST(InterpolationTestSuite, BilinearInterpolationMatrix)
    {
        Matrix m1 = Matrix({{0, 1, 2},
                            {1, 2, 3},
                            {2, 3, 4}});
        CHECK_EQUAL(0, Interpolate::bilinear(m1, 0, 0));
        CHECK_DOUBLES_EQUAL(0.4, Interpolate::bilinear(m1, 0.4, 0), 0.0001);
        CHECK_DOUBLES_EQUAL(0.6, Interpolate::bilinear(m1, 0.6, 0), 0.0001);
        CHECK_EQUAL(1, Interpolate::bilinear(m1, 1, 0));
        CHECK_DOUBLES_EQUAL(1.4, Interpolate::bilinear(m1, 1.4, 0), 0.0001);
        CHECK_DOUBLES_EQUAL(1.6, Interpolate::bilinear(m1, 1.6, 0), 0.0001);
        CHECK_DOUBLES_EQUAL(0.0, Interpolate::bilinear(m1, 2.4, 0), 0.0001);
        CHECK_DOUBLES_EQUAL(0.0, Interpolate::bilinear(m1, 2.6, 0), 0.0001);

        CHECK_EQUAL(1, Interpolate::bilinear(m1, 0, 1));
        CHECK_DOUBLES_EQUAL(1.4, Interpolate::bilinear(m1, 0.4, 1), 0.0001);
        CHECK_DOUBLES_EQUAL(1.6, Interpolate::bilinear(m1, 0.6, 1), 0.0001);
        CHECK_EQUAL(2, Interpolate::bilinear(m1, 1, 1));
        CHECK_DOUBLES_EQUAL(2.4, Interpolate::bilinear(m1, 1.4, 1), 0.0001);
        CHECK_DOUBLES_EQUAL(2.6, Interpolate::bilinear(m1, 1.6, 1), 0.0001);

        CHECK_DOUBLES_EQUAL(2.4, Interpolate::bilinear(m1, 0.4, 1.999), 0.01);
        CHECK_DOUBLES_EQUAL(2.6, Interpolate::bilinear(m1, 0.6, 1.999), 0.01);
        CHECK_DOUBLES_EQUAL(3.4, Interpolate::bilinear(m1, 1.4, 1.999), 0.01);
        CHECK_DOUBLES_EQUAL(3.6, Interpolate::bilinear(m1, 1.6, 1.999), 0.01);

        Matrix m2 = Matrix({{1, 2},
                            {4, 5},
                            {7, 8}});
        Matrix m2i_actual = Interpolate::interpolate(m2, 2, InterpolationType::BILINEAR);
        Matrix m2i_expected = Matrix({
            {1, 1.25, 1.5, 1.75},
            {2, 2.25, 2.5, 2.75},
            {3, 3.25, 3.5, 3.75},
            {4, 4.25, 4.5, 4.75},
            {5, 5.25, 5.5, 5.75},
            {6, 6.25, 6.5, 6.75},
        });
        CHECK(m2i_actual.is_close(m2i_expected, 0.01));
    }
}
