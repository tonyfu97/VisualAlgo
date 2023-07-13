#include "Gradients.hpp"
#include "helpers/Matrix.hpp"

#include <cmath>

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

    Matrix Gradients::computeGradientMagnitude(const Matrix& xGradient, const Matrix& yGradient) {
        Matrix result(xGradient.rows, xGradient.cols);

        for (int i = 0; i < xGradient.rows; i++) {
            for (int j = 0; j < xGradient.cols; j++) {
                result.set(i, j, sqrt(pow(xGradient.get(i, j), 2) + pow(yGradient.get(i, j), 2)));
            }
        }

        return result;
    }

    Matrix Gradients::computeGradientMagnitude(const Matrix& image) {
        Matrix xGradient = computeXGradient(image);
        Matrix yGradient = computeYGradient(image);

        return computeGradientMagnitude(xGradient, yGradient);
    }

    Matrix Gradients::computeGradientDirection(const Matrix& xGradient, const Matrix& yGradient) {
        Matrix result(xGradient.rows, xGradient.cols);

        for (int i = 0; i < xGradient.rows; i++) {
            for (int j = 0; j < xGradient.cols; j++) {
                result.set(i, j, atan2(yGradient.get(i, j), xGradient.get(i, j)));
            }
        }

        return result;
    }

    Matrix Gradients::computeGradientDirection(const Matrix& image) {
        Matrix xGradient = computeXGradient(image);
        Matrix yGradient = computeYGradient(image);

        return computeGradientDirection(xGradient, yGradient);
    }
}