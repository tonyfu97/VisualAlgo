#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "FeatureExtraction/Gradients.hpp"

#include <iostream>
#include <string>
#include <cmath>

const float TOLERANCE = 0.01;
const float MAX_PROPORTION_ABS_DIFF = 0.05;

static float proportion_abs_diff_exceed_tol(const VisualAlgo::Matrix& m1, const VisualAlgo::Matrix& m2)
{
    // Make sure both matrix are normalize
    VisualAlgo::Matrix m1_norm = m1;
    VisualAlgo::Matrix m2_norm = m2;   
    m1_norm.normalize();
    m2_norm.normalize();

    // Calculate the proportion of pixels that have an absolute difference greater than TOLERANCE
    int count = 0;
    for (int i = 0; i < m1_norm.rows; i++)
    {
        for (int j = 0; j < m1_norm.cols; j++)
        {
            if (std::abs(m1_norm.get(i, j) - m2_norm.get(i, j)) > TOLERANCE)
            {
                count++;
            }
        }
    }
    float proportion = static_cast<float>(count) / (m1_norm.rows * m1_norm.cols);
    return proportion;
}

static bool test_gradients(std::string img_name)
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
    
    float padetx = proportion_abs_diff_exceed_tol(image_x_gradient, image_x_gradient_expected);
    float padety = proportion_abs_diff_exceed_tol(image_y_gradient, image_y_gradient_expected);

    // std::cout << "Proportion of absolute difference exceeding tolerance for " << img_name << "_x_gradient.ppm: " << padetx << ", y_gradient.ppm: " << padety << std::endl;

    return (padetx < MAX_PROPORTION_ABS_DIFF) && (padety < MAX_PROPORTION_ABS_DIFF);
}

namespace VisualAlgo::FeatureExtraction
{
    TEST(GradientsTestSuite, GradientsCat)
    {
        CHECK(test_gradients("cat"));
    }

    TEST(GradientsTestSuite, GradientsLighthouse)
    {
        CHECK(test_gradients("lighthouse"));
    }
}
