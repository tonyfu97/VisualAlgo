#include "Blob.hpp"
#include "helpers/Matrix.hpp"
#include "helpers/ProgressBar.hpp"
#include "Filter.hpp"

#include <map>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <string>

namespace VisualAlgo::FeatureExtraction
{
    std::vector<std::tuple<int, int, float>> Blob::findLocalMaxima(const std::vector<Matrix> &scale_space, const std::vector<float> &sigmas, int window_size, float threshold) const
    {
        if (window_size % 2 == 0)
            throw std::invalid_argument("Window size must be odd.");

        const int ROWS = scale_space.front().rows;
        const int COLS = scale_space.front().cols;

        std::vector<std::tuple<int, int, float>> maxima;
        int half_window = window_size / 2;

        for (size_t iter = 0; iter < scale_space.size(); ++iter)
        {
            Matrix const &matrix = scale_space[iter];

            int scale_window = std::min((size_t)half_window, std::min(iter, scale_space.size() - iter - 1));

            for (int i = half_window; i < ROWS - half_window; i++)
            {
                for (int j = half_window; j < COLS - half_window; j++)
                {
                    float currVal = matrix.get(i, j);
                    bool isMaxima = true;
                    for (int si = -scale_window; si <= scale_window && isMaxima; si++)
                    {
                        for (int xi = -half_window; xi <= half_window && isMaxima; xi++)
                        {
                            for (int yi = -half_window; yi <= half_window && isMaxima; yi++)
                            {
                                if (scale_space[iter + si].get(i + xi, j + yi) > currVal)
                                {
                                    isMaxima = false;
                                    break;
                                }
                            }
                        }
                    }

                    if (isMaxima && currVal > threshold)
                    {
                        maxima.push_back(std::make_tuple(i, j, sigmas[iter]));
                    }
                }
            }
        }
        return maxima;
    }

    BlobDoG::BlobDoG(float initial_sigma, float k, float threshold, int window_size, int octaves)
        : initial_sigma(initial_sigma), k(k), threshold(threshold), window_size(window_size), octaves(octaves)
    {
    }

    Matrix BlobDoG::apply(const Matrix &image) const
    {
        Matrix result(image.rows, image.cols);
        auto corners = detect(image);
        for (auto corner : corners)
        {
            result.set(std::get<0>(corner), std::get<1>(corner), static_cast<float>(std::get<2>(corner)));
        }
        return result;
    }

    std::vector<std::tuple<int, int, float>> BlobDoG::detect(const Matrix &image) const
    {
        ProgressBar progress_bar(octaves + 1, "BlobDoG detection");
        std::vector<Matrix> DoG_space;
        float sigma = initial_sigma;
        Matrix prev_blurred;
        std::vector<float> sigmas;

        for (int i = 0; i < octaves + 1; i++)
        {
            GaussianFilter g(sigma);
            Matrix blurred = g.apply(image);
            if (i > 0)
            {
                progress_bar.step("Applying DoG filter of sigma = " + std::to_string(sigma) + "...");
                DoG_space.push_back((blurred - prev_blurred) * (sigma * sigma));
            }
            prev_blurred = blurred;
            sigma *= k;
            sigmas.push_back(sigma);
        }

        progress_bar.step("Finding local maxima...");
        return findLocalMaxima(DoG_space, sigmas, window_size, threshold);
    }

    BlobLoG::BlobLoG(float initial_sigma, float k, float threshold, int window_size, int octaves)
        : initial_sigma(initial_sigma), k(k), threshold(threshold), window_size(window_size), octaves(octaves)
    {
    }

    Matrix BlobLoG::apply(const Matrix &image) const
    {
        Matrix result(image.rows, image.cols);
        auto corners = detect(image);
        for (auto corner : corners)
        {
            result.set(std::get<0>(corner), std::get<1>(corner), static_cast<float>(std::get<2>(corner)));
        }
        return result;
    }

    std::vector<std::tuple<int, int, float>> BlobLoG::detect(const Matrix &image) const
    {
        ProgressBar progress_bar(octaves + 1, "BlobLoG detection");
        std::vector<Matrix> LoG_space;
        float sigma = initial_sigma;
        std::vector<float> sigmas;
        sigmas.push_back(sigma);

        for (int i = 0; i < octaves; i++)
        {
            progress_bar.step("Applying LoG filter of sigma = " + std::to_string(sigma) + "...");
            LoGFilter g(sigma);
            Matrix LoG = g.apply(image);
            LoG_space.push_back(LoG * (sigma * sigma));
            sigma *= k;
            sigmas.push_back(sigma);
        }

        progress_bar.step("Finding local maxima...");
        return findLocalMaxima(LoG_space, sigmas, window_size, threshold);
    }

}