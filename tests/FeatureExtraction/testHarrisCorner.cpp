#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "FeatureExtraction/Harris.hpp"
#include "test_utils.hpp"

#include <iostream>
#include <string>
#include <cmath>

const float MAX_PROPORTION_ABS_DIFF = 0.05f;
const float SIGMA = 1.0f;
const float K = 0.04f;
const float THRESHOLD = 0.01f;

static bool test_harris(std::string img_name, float sigma, float k, float threshold)
{
    VisualAlgo::Matrix image, image_harris_expected;
    image.load("datasets/FeatureExtraction/" + img_name + "_resized.ppm");
    image_harris_expected.load("datasets/FeatureExtraction/" + img_name + "_expected_harris.ppm");

    image.normalize();
    image_harris_expected.normalize();

    VisualAlgo::FeatureExtraction::Harris harris(sigma, k, threshold);
    VisualAlgo::Matrix image_harris = harris.apply(image);

    image_harris.save("datasets/FeatureExtraction/" + img_name + "_harris.ppm", true);

    float padet = proportionAbsDiffExceedTol(image_harris, image_harris_expected);

    // std::cout << "Proportion of absolute difference exceeding tolerance for " << img_name << "_harris.ppm: " << padet << std::endl;

    return (padet < MAX_PROPORTION_ABS_DIFF);
}

namespace VisualAlgo::FeatureExtraction
{
    TEST(HarrisTestSuite, HarrisCat)
    {
        CHECK(test_harris("cat", SIGMA, K, THRESHOLD));
    }

    TEST(HarrisTestSuite, HarrisLighthouse)
    {
        CHECK(test_harris("lighthouse", SIGMA, K, THRESHOLD));
    }
}
