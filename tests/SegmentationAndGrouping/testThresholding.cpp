#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "SegmentationAndGrouping/Thresholding.hpp"
#include "FeatureExtraction/Filter.hpp"

namespace VisualAlgo::SegmentationAndGrouping
{
    TEST(ThresholdingTestSuite, Coins)
    {
        Matrix image;
        image.load("datasets/SegmentationAndGrouping/coins.ppm");
        Matrix actual = Thresholding::apply(image, 130);
        actual.save("datasets/SegmentationAndGrouping/coins_thresholding.ppm", true);

        CHECK_EQUAL(image.rows, actual.rows);
        CHECK_EQUAL(image.cols, actual.cols);
    }

    TEST(ThresholdingTestSuite, CoinsMedianAndThresholding)
    {
        Matrix image;
        image.load("datasets/SegmentationAndGrouping/coins.ppm");

        VisualAlgo::FeatureExtraction::MedianFilter medianFilter(5);
        Matrix image_median = medianFilter.apply(image);
        image_median.save("datasets/SegmentationAndGrouping/coins_median.ppm", true);

        Matrix actual = Thresholding::apply(image_median, 130);
        actual.save("datasets/SegmentationAndGrouping/coins_median_thresholding.ppm", true);

        actual = medianFilter.apply(actual);
        actual.save("datasets/SegmentationAndGrouping/coins_median_thresholding_median.ppm", true);

        CHECK_EQUAL(image.rows, actual.rows);
        CHECK_EQUAL(image.cols, actual.cols);
    }
}