#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "FeatureExtraction/Gradients.hpp"
#include "test_utils.hpp"

#include <iostream>
#include <string>
#include <cmath>

const float MAX_PROPORTION_ABS_DIFF = 0.05;

static bool test_gradients_xy(std::string img_name)
{
    VisualAlgo::Matrix image, image_x_gradient_expected, image_y_gradient_expected;
    image.load("datasets/FeatureExtraction/" + img_name + "_resized.ppm");
    image_x_gradient_expected.load("datasets/FeatureExtraction/" + img_name + "_expected_sobel_x.ppm");
    image_y_gradient_expected.load("datasets/FeatureExtraction/" + img_name + "_expected_sobel_y.ppm");

    image.normalize();
    image_x_gradient_expected.normalize();
    image_y_gradient_expected.normalize();

    VisualAlgo::Matrix image_x_gradient, image_y_gradient;
    image_x_gradient = VisualAlgo::FeatureExtraction::Gradients::computeXGradient(image);
    image_y_gradient = VisualAlgo::FeatureExtraction::Gradients::computeYGradient(image);

    image_x_gradient.save("datasets/FeatureExtraction/" + img_name + "_x_gradient.ppm", true);
    image_y_gradient.save("datasets/FeatureExtraction/" + img_name + "_y_gradient.ppm", true);

    float padetx = proportionAbsDiffExceedTol(image_x_gradient, image_x_gradient_expected);
    float padety = proportionAbsDiffExceedTol(image_y_gradient, image_y_gradient_expected);

    // std::cout << "Proportion of absolute difference exceeding tolerance for " << img_name << "_x_gradient.ppm: " << padetx << ", y_gradient.ppm: " << padety << std::endl;

    return (padetx < MAX_PROPORTION_ABS_DIFF) && (padety < MAX_PROPORTION_ABS_DIFF);
}

static bool test_gradients_magnitude(std::string img_name)
{
    VisualAlgo::Matrix image, image_gradient_magnitude_expected;
    image.load("datasets/FeatureExtraction/" + img_name + "_resized.ppm");
    image_gradient_magnitude_expected.load("datasets/FeatureExtraction/" + img_name + "_expected_grad_magnitude.ppm");

    VisualAlgo::Matrix image_gradient_magnitude;
    image_gradient_magnitude = VisualAlgo::FeatureExtraction::Gradients::computeGradientMagnitude(image);

    image_gradient_magnitude.save("datasets/FeatureExtraction/" + img_name + "_grad_magnitude.ppm", true);

    float padet = proportionAbsDiffExceedTol(image_gradient_magnitude, image_gradient_magnitude_expected);

    // std::cout << "Proportion of absolute difference exceeding tolerance for " << img_name << "_grad_magnitude.ppm: " << padet << std::endl;

    return padet < MAX_PROPORTION_ABS_DIFF;
}

static bool test_gradients_direction(std::string img_name)
{
    VisualAlgo::Matrix image, image_gradient_direction_expected;
    image.load("datasets/FeatureExtraction/" + img_name + "_resized.ppm");
    image_gradient_direction_expected.load("datasets/FeatureExtraction/" + img_name + "_expected_grad_direction.ppm");

    VisualAlgo::Matrix image_gradient_direction;
    image_gradient_direction = VisualAlgo::FeatureExtraction::Gradients::computeGradientDirection(image);

    image_gradient_direction.save("datasets/FeatureExtraction/" + img_name + "_grad_direction.ppm", true);

    float padet = proportionAbsDiffExceedTol(image_gradient_direction, image_gradient_direction_expected, 0.1); // tolerance is 0.1 because the gradient direction is not as accurate as the gradient magnitude. And also because the gradient direction is in unit radians, so the difference is not as obvious as the gradient magnitude.

    // std::cout << "Proportion of absolute difference exceeding tolerance for " << img_name << "_grad_direction.ppm: " << padet << std::endl;

    return padet < MAX_PROPORTION_ABS_DIFF;
}

namespace VisualAlgo::FeatureExtraction
{
    TEST(GradientsTestSuite, GradientsCat)
    {
        CHECK(test_gradients_xy("cat"));
        CHECK(test_gradients_magnitude("cat"));
        CHECK(test_gradients_direction("cat"));
    }

    TEST(GradientsTestSuite, GradientsLighthouse)
    {
        CHECK(test_gradients_xy("lighthouse"));
        CHECK(test_gradients_magnitude("lighthouse"));
        CHECK(test_gradients_direction("lighthouse"));
    }
}
