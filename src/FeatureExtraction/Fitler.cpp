#include "FeatureExtraction/Filter.hpp"
#include "helpers/Matrix.hpp"

#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <vector>

namespace VisualAlgo::FeatureExtraction
{

    GaussianFilter::GaussianFilter(float sigma)
    {
        if (sigma <= 0)
            throw std::invalid_argument("Sigma must be positive");
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

    LoGFilter::LoGFilter(float sigma)
    {
        this->sigma = sigma;
        this->kernel = computeLoGKernel(sigma);
    }

    Matrix LoGFilter::apply(const Matrix &image) const
    {
        return image.convolve(kernel);
    }

    Matrix LoGFilter::computeLoGKernel(float sigma) const
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
                float value = (x * x + y * y - 2 * sigma * sigma) * exp(-(x * x + y * y) / (2 * sigma * sigma));
                kernel.set(i, j, value);
                sum += value;
            }
        }

        return kernel / sum;
    }

    MedianFilter::MedianFilter(int size) : size(size)
    {
        if (size <= 0)
            throw std::invalid_argument("Size must be positive");
        if (size % 2 == 0)
            throw std::invalid_argument("Size must be odd");
    }

    Matrix MedianFilter::apply(const Matrix &image) const
    {
        Matrix result = image;

        for (int i = 0; i < image.rows; ++i)
        {
            for (int j = 0; j < image.cols; ++j)
            {
                result.set(i, j, compute_median(image, i, j, size));
            }
        }

        return result;
    }

    float MedianFilter::compute_median(const Matrix &image, int row, int col, int size) const
    {
        std::vector<float> neighborhood;

        for (int i = -size / 2; i <= size / 2; ++i)
        {
            for (int j = -size / 2; j <= size / 2; ++j)
            {
                if (row + i < 0 || row + i >= image.rows || col + j < 0 || col + j >= image.cols)
                    continue;
                neighborhood.push_back(image.get(row + i, col + j));
            }
        }

        if (neighborhood.size() % 2 == 0)
        {
            std::nth_element(neighborhood.begin(), neighborhood.begin() + neighborhood.size() / 2, neighborhood.end());
            std::nth_element(neighborhood.begin(), neighborhood.begin() + neighborhood.size() / 2 - 1, neighborhood.end());
            return (neighborhood[neighborhood.size() / 2] + neighborhood[neighborhood.size() / 2 - 1]) / 2;
        }

        std::nth_element(neighborhood.begin(), neighborhood.begin() + neighborhood.size() / 2, neighborhood.end());
        return neighborhood[neighborhood.size() / 2];
    }

}