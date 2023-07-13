#include "FeatureExtraction/Filter.hpp"
#include "helpers/Matrix.hpp"

#include <cmath>

namespace VisualAlgo::FeatureExtraction
{

    GaussianFilter::GaussianFilter(float sigma)
    {
        this->sigma = sigma;
        this->kernel = computeGaussianKernel(sigma);
    }

    Matrix GaussianFilter::apply(const Matrix &image) const
    {
        return image.convolve(kernel);
    }

    Matrix GaussianFilter::computeGaussianKernel(float sigma) const
    {
        int size = 2 * ceil(3 * sigma) + 1;
        Matrix kernel(size, size);

        float sum = 0.0f;
        for (int i = 0; i < size; i++)
        {
            int x = i - size / 2;
            for (int j = 0; j < size; j++)
            {
                int y = j - size / 2;
                float value = exp(-(x * x + y * y) / (2 * sigma * sigma));
                kernel.set(i, j, value);
                sum += value;
            }
        }

        return kernel / sum;
    }

    SobelFilterX::SobelFilterX()
    {
        this->kernel = Matrix({{1, 0, -1},
                               {2, 0, -2},
                               {1, 0, -1}});
    }

    Matrix SobelFilterX::apply(const Matrix &image) const
    {
        return image.convolve(kernel);
    }

    SobelFilterY::SobelFilterY()
    {
        this->kernel = Matrix({{1, 2, 1},
                               {0, 0, 0},
                               {-1, -2, -1}});
    }

    Matrix SobelFilterY::apply(const Matrix &image) const
    {
        return image.convolve(kernel);
    }
}