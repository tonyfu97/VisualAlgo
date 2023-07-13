#include "helpers/Matrix.hpp"
#include "FeatureExtraction/Gradients.hpp"
#include "FeatureExtraction/Filter.hpp"

#include <cmath>

namespace VisualAlgo::FeatureExtraction
{
    Matrix Gradients::computeXGradient(const Matrix &image)
    {
        SobelFilterX filter;
        return filter.apply(image);
    }

    Matrix Gradients::computeYGradient(const Matrix &image)
    {
        SobelFilterY filter;
        return filter.apply(image);
    }

    Matrix Gradients::computeGradientMagnitude(const Matrix &xGradient, const Matrix &yGradient)
    {
        Matrix result(xGradient.rows, xGradient.cols);

        for (int i = 0; i < xGradient.rows; i++)
        {
            for (int j = 0; j < xGradient.cols; j++)
            {
                result.set(i, j, sqrt(pow(xGradient.get(i, j), 2) + pow(yGradient.get(i, j), 2)));
            }
        }

        return result;
    }

    Matrix Gradients::computeGradientMagnitude(const Matrix &image)
    {
        Matrix xGradient = computeXGradient(image);
        Matrix yGradient = computeYGradient(image);

        return computeGradientMagnitude(xGradient, yGradient);
    }

    Matrix Gradients::computeGradientDirection(const Matrix &xGradient, const Matrix &yGradient, float threshold)
    {
        Matrix result(xGradient.rows, xGradient.cols);

        for (int i = 0; i < xGradient.rows; i++)
        {
            for (int j = 0; j < xGradient.cols; j++)
            {
                float xGrad = xGradient.get(i, j);
                float yGrad = yGradient.get(i, j);
                float magnitude = sqrt(xGrad * xGrad + yGrad * yGrad);

                if (magnitude >= threshold)
                {
                    result.set(i, j, atan2(yGrad, xGrad));
                }
                else
                {
                    result.set(i, j, 0.0f);
                }
            }
        }

        return result;
    }

    Matrix Gradients::computeGradientDirection(const Matrix &image)
    {
        Matrix xGradient = computeXGradient(image);
        Matrix yGradient = computeYGradient(image);

        return computeGradientDirection(xGradient, yGradient);
    }
}