#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "FeatureExtraction/Filter.hpp"
#include "test_utils.hpp"

#include <iostream>
#include <string>
#include <cmath>

const float MAX_PROPORTION_ABS_DIFF = 0.05f;
const float SIGMA = 3.0f;

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
    
    float padet = proportionAbsDiffExceedTol(image_gaussian, image_gaussian_expected);

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
