#include "Harris.hpp"
#include "Gradients.hpp"
#include "Filter.hpp"
#include "helpers/Matrix.hpp"
#include "helpers/ProgressBar.hpp"

#include <stdexcept>

namespace VisualAlgo::FeatureExtraction
{

    Harris::Harris(float sigma, float k, float threshold)
        : sigma(sigma), k(k), threshold(threshold)
    {
        if (sigma <= 0)
            throw std::invalid_argument("Sigma must be positive");

        if (k <= 0)
            throw std::invalid_argument("K must be positive");
    }

    Matrix Harris::apply(const Matrix &image) const
    {
        Matrix result(image.rows, image.cols);
        auto corners = detect(image, sigma, k, threshold);
        for (auto corner : corners)
        {
            result.set(corner.first, corner.second, 1);
        }
        return result;
    }

    std::vector<std::pair<int, int>> Harris::detect(const Matrix &image, float sigma, float k, float threshold)
    {
        ProgressBar progress_bar(5, "Harris corner detection");
        // Step 1: Compute gradients
        progress_bar.step("Computing gradients...");
        Matrix Ix = Gradients::computeXGradient(image);
        Matrix Iy = Gradients::computeYGradient(image);

        // Step 2: Compute (element-wise) products of gradients
        progress_bar.step("Computing products of gradients...");
        Matrix Ixx = Ix * Ix;
        Matrix Iyy = Iy * Iy;
        Matrix Ixy = Ix * Iy;

        // Step 3: Apply Gaussian filter
        progress_bar.step("Applying Gaussian filter...");
        GaussianFilter g(sigma);
        Matrix Gxx = g.apply(Ixx);
        Matrix Gyy = g.apply(Iyy);
        Matrix Gxy = g.apply(Ixy);

        // Step 4: Calculate corner response function (R)
        progress_bar.step("Calculating corner response function...");
        Matrix R(image.rows, image.cols);
        for (int i = 0; i < image.rows; ++i)
        {
            for (int j = 0; j < image.cols; ++j)
            {
                float det = Gxx.get(i, j) * Gyy.get(i, j) - Gxy.get(i, j) * Gxy.get(i, j);
                float trace = Gxx.get(i, j) + Gyy.get(i, j);
                R.set(i, j, det - k * trace * trace);
            }
        }

        // Step 5: Threshold the corner response function
        progress_bar.step("Thresholding...");
        std::vector<std::pair<int, int>> corners;
        for (int i = 0; i < R.rows; ++i)
        {
            for (int j = 0; j < R.cols; ++j)
            {
                if (R.get(i, j) > threshold)
                {
                    corners.push_back({i, j});
                }
            }
        }
        return corners;
    }

}
