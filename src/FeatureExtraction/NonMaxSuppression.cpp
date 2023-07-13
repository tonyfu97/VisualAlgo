#include "FeatureExtraction/NonMaxSuppression.hpp"
#include "helpers/Matrix.hpp"

#include <cmath>

namespace VisualAlgo::FeatureExtraction
{
    Matrix NonMaxSuppression::apply(const Matrix &gradientMagnitude, const Matrix &gradientDirection)
    {
        Matrix result(gradientMagnitude.rows, gradientMagnitude.cols);

        for (int i = 1; i < gradientMagnitude.rows - 1; i++)
        {
            for (int j = 1; j < gradientMagnitude.cols - 1; j++)
            {
                float direction = gradientDirection.get(i, j);

                // approximate the direction to four possible directions
                float roundedDirection = round(direction / (M_PI / 4)) * (M_PI / 4);

                int dx = round(cos(roundedDirection));
                int dy = round(sin(roundedDirection));

                // compare with the neighboring pixels in the gradient direction
                if (gradientMagnitude.get(i, j) > gradientMagnitude.get(i + dy, j + dx) &&
                    gradientMagnitude.get(i, j) > gradientMagnitude.get(i - dy, j - dx))
                {
                    result.set(i, j, gradientMagnitude.get(i, j));
                }
            }
        }

        return result;
    }
}
