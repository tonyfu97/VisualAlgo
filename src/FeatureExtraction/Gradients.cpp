#include "Gradients.hpp"
#include "helpers/matrix.hpp"

namespace VisualAlgo::FeatureExtraction {
    Matrix Gradients::computeXGradient(const Matrix& image) {
        Matrix sobelX = Matrix({
            {1, 0, -1},
            {2, 0, -2},
            {1, 0, -1}
        });

        return image.convolve(sobelX);
    }

    Matrix Gradients::computeYGradient(const Matrix& image) {
        Matrix sobelY = Matrix({
            {1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1}
        });

        return image.convolve(sobelY);
    }
}