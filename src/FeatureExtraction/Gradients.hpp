#pragma once

#include "helpers/Matrix.hpp"

namespace VisualAlgo::FeatureExtraction {
    class Gradients {
    public:
        static Matrix computeXGradient(const Matrix& image);
        static Matrix computeYGradient(const Matrix& image);
    };
}
