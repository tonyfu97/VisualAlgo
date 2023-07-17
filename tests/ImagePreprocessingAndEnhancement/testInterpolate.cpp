#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "ImagePreprocessingAndEnhancement/Interpolate.hpp"
#include "test_utils.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>

const float MAX_PROPORTION_ABS_DIFF = 0.2f;
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
}
