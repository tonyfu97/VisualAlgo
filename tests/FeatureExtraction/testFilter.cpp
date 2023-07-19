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

    TEST(MedianFilter, MedianFilterMatrix)
    {
        Matrix image = Matrix({{1, 2, 3, 4, 5},
                               {6, 7, 8, 9, 10},
                               {11, 12, 13, 14, 15},
                               {16, 17, 18, 19, 20},
                               {21, 22, 23, 24, 25}});

        Matrix expected = Matrix({{4, 4.5, 5.5, 6.5, 7},
                                  {6.5, 7, 8, 9, 9.5},
                                  {11.5, 12, 13, 14, 14.5},
                                  {16.5, 17, 18, 19, 19.5},
                                  {19, 19.5, 20.5, 21.5, 22}});

        MedianFilter medianFilter(3);
        Matrix actual = medianFilter.apply(image);
        CHECK(actual.is_close(expected, 0.0001f));
    }
}
