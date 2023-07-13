#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "FeatureExtraction/Canny.hpp"
#include "test_utils.hpp"

#include <iostream>
#include <string>
#include <cmath>

const float MAX_PROPORTION_ABS_DIFF = 0.05f;
const float SIGMA = 1.0f;
const float LOW_THRESHOLD = 0.1f;
const float HIGH_THRESHOLD = 0.2f;

static bool test_canny(std::string img_name, float sigma, float low_threshold, float high_threshold)
{
    VisualAlgo::Matrix image, image_canny_expected;
    image.load("datasets/FeatureExtraction/" + img_name + "_resized.ppm");
    image_canny_expected.load("datasets/FeatureExtraction/" + img_name + "_expected_canny.ppm");

    image.normalize();
    image_canny_expected.normalize();

    VisualAlgo::FeatureExtraction::Canny canny(sigma, low_threshold, high_threshold);
    VisualAlgo::Matrix image_canny = canny.apply(image);

    image_canny.save("datasets/FeatureExtraction/" + img_name + "_canny.ppm", true);

    float padet = proportionAbsDiffExceedTol(image_canny, image_canny_expected);

    // std::cout << "Proportion of absolute difference exceeding tolerance for " << img_name << "_canny.ppm: " << padet << std::endl;

    return (padet < MAX_PROPORTION_ABS_DIFF);
}

namespace VisualAlgo::FeatureExtraction
{
    TEST(CannyTestSuite, CannyCat)
    {
        CHECK(test_canny("cat", SIGMA, LOW_THRESHOLD, HIGH_THRESHOLD));
    }

    TEST(CannyTestSuite, CannyLighthouse)
    {
        CHECK(test_canny("lighthouse", SIGMA, LOW_THRESHOLD, HIGH_THRESHOLD));
    }
}
