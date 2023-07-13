#pragma once

#include "helpers/Matrix.hpp"
#include "FeatureExtraction/EdgeNonMaxSuppression.hpp"
#include "FeatureExtraction/Filter.hpp"
#include "FeatureExtraction/Gradients.hpp"

namespace VisualAlgo::FeatureExtraction
{
    class Canny {
    public:
        Canny(float sigma, float low_threshold, float high_threshold);
        Matrix apply(const Matrix& image);

    private:
        float _sigma;
        float low_threshold;
        float high_threshold;
        GaussianFilter gaussian_filter;
        SobelFilterX sobel_filter_x;
        SobelFilterY sobel_filter_y;
        EdgeNonMaxSuppression non_max_suppression;

        Matrix applyThreshold(const Matrix& image);
        Matrix trackEdges(const Matrix& image);
    };
}
