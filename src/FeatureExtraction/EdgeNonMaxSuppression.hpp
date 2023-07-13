#pragma once

#include "helpers/Matrix.hpp"

namespace VisualAlgo::FeatureExtraction
{
    class EdgeNonMaxSuppression {
    public:
        static Matrix apply(const Matrix& image);
        static Matrix apply(const Matrix& gradientMagnitude, const Matrix& gradientDirection);
    };
}
