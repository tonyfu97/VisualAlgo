#include "HistogramEqualization.hpp"
#include "helpers/Matrix.hpp"

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    Matrix HistogramEqualization::equalize(const Matrix &img)
    {
        std::map<float, int> histogram = calculate_histogram(img);
        std::map<float, float> cdf = calculate_cumulative_distribution_function(histogram, img.rows * img.cols);

        Matrix result = img;
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                float pixel_value = img.get(i, j);
                result.set(i, j, cdf[pixel_value]);
            }
        }

        result.normalize255();
        return result;
    }

    std::map<float, int> HistogramEqualization::calculate_histogram(const Matrix &img)
    {
        std::map<float, int> histogram;
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                histogram[img.get(i, j)]++;
            }
        }
        return histogram;
    }

    std::map<float, float> HistogramEqualization::calculate_cumulative_distribution_function(const std::map<float, int> &histogram, int num_pixels)
    {
        std::map<float, float> cdf;
        float cum_sum = 0;
        for (auto &it : histogram)
        {
            cum_sum += static_cast<float>(it.second) / num_pixels;
            cdf[it.first] = cum_sum;
        }
        return cdf;
    }

}
