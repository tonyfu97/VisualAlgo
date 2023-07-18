#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "ImagePreprocessingAndEnhancement/HistogramEqualization.hpp"

#include <iostream>
#include <map>
#include <cmath>
#include <numeric>

const float MIN_CORRELATION = 0.95;

static std::map<float, float> calculate_cdf(const VisualAlgo::Matrix &image)
{
    std::map<float, int> histogram;
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            histogram[image.get(i, j)]++;
        }
    }

    std::map<float, float> cdf;
    float cum_sum = 0;
    for (auto &it : histogram)
    {
        cum_sum += static_cast<float>(it.second) / (image.rows * image.cols);
        cdf[it.first] = cum_sum;
    }
    return cdf;
}

static float calculate_correlation(const std::map<float, float> &data)
{
    int n = data.size();
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, sum_y2 = 0;

    for (const auto &[x, y] : data)
    {
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x2 += x * x;
        sum_y2 += y * y;
    }

    float numerator = n * sum_xy - sum_x * sum_y;
    float denominator = std::sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));

    if (denominator != 0)
    {
        return numerator / denominator;
    }
    else
    {
        // if the denominator is zero return 0
        return 0;
    }
}

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    TEST(HistogramEqualizationTestSuite, LighthouseDark)
    {
        Matrix image;
        image.load("datasets/ImagePreprocessingAndEnhancement/lighthouse_dark.ppm");
        Matrix actual = HistogramEqualization::equalize(image);
        actual.save("datasets/ImagePreprocessingAndEnhancement/lighthouse_dark_equalized.ppm", true);

        CHECK_EQUAL(image.rows, actual.rows);
        CHECK_EQUAL(image.cols, actual.cols);

        auto cdf = calculate_cdf(actual);
        float correlation = calculate_correlation(cdf);
        CHECK(correlation > MIN_CORRELATION);
    }

    TEST(HistogramEqualizationTestSuite, LighthouseBright)
    {
        Matrix image;
        image.load("datasets/ImagePreprocessingAndEnhancement/lighthouse_bright.ppm");
        Matrix actual = HistogramEqualization::equalize(image);
        actual.save("datasets/ImagePreprocessingAndEnhancement/lighthouse_bright_equalized.ppm", true);

        CHECK_EQUAL(image.rows, actual.rows);
        CHECK_EQUAL(image.cols, actual.cols);

        auto cdf = calculate_cdf(actual);
        float correlation = calculate_correlation(cdf);
        CHECK(correlation > MIN_CORRELATION);
    }

    TEST(HistogramEqualizationTestSuite, LighthouseWeakContrast)
    {
        Matrix image;
        image.load("datasets/ImagePreprocessingAndEnhancement/lighthouse_weak_contrast.ppm");
        Matrix actual = HistogramEqualization::equalize(image);
        actual.save("datasets/ImagePreprocessingAndEnhancement/lighthouse_weak_contrast_equalized.ppm", true);

        CHECK_EQUAL(image.rows, actual.rows);
        CHECK_EQUAL(image.cols, actual.cols);

        auto cdf = calculate_cdf(actual);
        float correlation = calculate_correlation(cdf);
        CHECK(correlation > MIN_CORRELATION);
    }

    TEST(HistogramEqualizationTestSuite, LighthouseStrongContrast)
    {
        Matrix image;
        image.load("datasets/ImagePreprocessingAndEnhancement/lighthouse_strong_contrast.ppm");
        Matrix actual = HistogramEqualization::equalize(image);
        actual.save("datasets/ImagePreprocessingAndEnhancement/lighthouse_strong_contrast_equalized.ppm", true);

        CHECK_EQUAL(image.rows, actual.rows);
        CHECK_EQUAL(image.cols, actual.cols);

        auto cdf = calculate_cdf(actual);
        float correlation = calculate_correlation(cdf);
        CHECK(correlation > MIN_CORRELATION);
    }

}