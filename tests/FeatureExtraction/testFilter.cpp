#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "FeatureExtraction/Filter.hpp"

#include <iostream>
#include <string>
#include <cmath>

const float TOLERANCE = 0.01;
const float MAX_PROPORTION_ABS_DIFF = 0.05;
const float SIGMA = 3.0;

static float proportion_abs_diff_exceed_tol(const VisualAlgo::Matrix& m1, const VisualAlgo::Matrix& m2, float tol=TOLERANCE)
{
    // Make sure both matrices are normalized
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
            if (std::abs(m1_norm.get(i, j) - m2_norm.get(i, j)) > tol)
            {
                count++;
            }
        }
    }
    float proportion = static_cast<float>(count) / (m1_norm.rows * m1_norm.cols);
    return proportion;
}

static bool test_gaussian_filter(std::string img_name, float sigma)
{
    VisualAlgo::Matrix image, image_gaussian_expected;
    image.load("datasets/FeatureExtraction/" + img_name + "_resized.ppm");
    image_gaussian_expected.load("datasets/FeatureExtraction/" + img_name + "_expected_gaussian.ppm");

    image.normalize();
    image_gaussian_expected.normalize();

    VisualAlgo::FeatureExtraction::GaussianFilter gaussianFilter(sigma);
    VisualAlgo::Matrix image_gaussian = gaussianFilter.apply(image);

    image_gaussian.save("datasets/FeatureExtraction/" + img_name + "_gaussian.ppm", true);
    
    float padet = proportion_abs_diff_exceed_tol(image_gaussian, image_gaussian_expected);

    // std::cout << "Proportion of absolute difference exceeding tolerance for " << img_name << "_gaussian.ppm: " << padet << std::endl;

    return (padet < MAX_PROPORTION_ABS_DIFF);
}

namespace VisualAlgo::FeatureExtraction
{
    TEST(GaussianFilterTestSuite, GaussianFilterCat)
    {
        CHECK(test_gaussian_filter("cat", SIGMA));
    }

    TEST(GaussianFilterTestSuite, GaussianFilterLighthouse)
    {
        CHECK(test_gaussian_filter("lighthouse", SIGMA));
    }
}
