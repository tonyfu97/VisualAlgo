#pragma once

#include "helpers/Matrix.hpp"

namespace VisualAlgo::FeatureExtraction {
    class Gradients {
    public:
        static Matrix computeXGradient(const Matrix& image);
        static Matrix computeYGradient(const Matrix& image);
        static Matrix computeGradientMagnitude(const Matrix& xGradient, const Matrix& yGradient);
        static Matrix computeGradientMagnitude(const Matrix& image);
        static Matrix computeGradientDirection(const Matrix& xGradient, const Matrix& yGradient);
        static Matrix computeGradientDirection(const Matrix& image);
    };
}
