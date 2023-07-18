#pragma once

#include <vector>
#include <map>
#include "helpers/Matrix.hpp"

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    class HistogramEqualization
    {
    public:
        static Matrix equalize(const Matrix &img);

    private:
        static std::map<float, int> calculate_histogram(const Matrix &img);
        static std::map<float, float> calculate_cumulative_distribution_function(const std::map<float, int> &histogram, int num_pixels);
    };

}
