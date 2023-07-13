#include "FeatureExtraction/EdgeNonMaxSuppression.hpp"
#include "FeatureExtraction/Gradients.hpp"
#include "helpers/Matrix.hpp"

#include <cmath>

namespace VisualAlgo::FeatureExtraction
{
    Matrix EdgeNonMaxSuppression::apply(const Matrix &image)
    {
        Matrix xGradient = Gradients::computeXGradient(image);
        Matrix yGradient = Gradients::computeYGradient(image);

        Matrix gradientMagnitude = Gradients::computeGradientMagnitude(xGradient, yGradient);
        Matrix gradientDirection = Gradients::computeGradientDirection(xGradient, yGradient);

        return apply(gradientMagnitude, gradientDirection);
    }

    Matrix EdgeNonMaxSuppression::apply(const Matrix &gradientMagnitude, const Matrix &gradientDirection)
    {
        Matrix result(gradientMagnitude.rows, gradientMagnitude.cols);

        for (int i = 1; i < gradientMagnitude.rows - 1; i++)
        {
            for (int j = 1; j < gradientMagnitude.cols - 1; j++)
            {
                float direction = gradientDirection.get(i, j);

                // 1. Round the gradient direction to one of four possible directions: 0, 45, 90, 135
                float roundedDirection = round(direction / (M_PI / 4)) * (M_PI / 4);

                int dx = round(cos(roundedDirection));
                int dy = round(sin(roundedDirection));

                // 2. Compuare with neighbors in the gradient direction
                if (gradientMagnitude.get(i, j) > gradientMagnitude.get(i + dy, j + dx) &&
                    gradientMagnitude.get(i, j) > gradientMagnitude.get(i - dy, j - dx))
                {   
                    // 3. If the magnitude is greater than both neighbors, set it in the output image.
                    result.set(i, j, gradientMagnitude.get(i, j));
                }
            }
        }

        return result;
    }
}
