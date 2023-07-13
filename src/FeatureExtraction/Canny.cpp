#include "FeatureExtraction/Canny.hpp"
#include "helpers/ProgressBar.hpp"

namespace VisualAlgo::FeatureExtraction
{
    Canny::Canny(float sigma, float low_threshold, float high_threshold) : _sigma(sigma), low_threshold(low_threshold), high_threshold(high_threshold), gaussian_filter(_sigma), sobel_filter_x(), sobel_filter_y(), non_max_suppression()
    {
    }

    Matrix Canny::apply(const Matrix &image)
    {
        ProgressBar progress_bar(6, "Canny edge detection");
        progress_bar.step("Applying Gaussian smoothing...");
        Matrix smoothed = gaussian_filter.apply(image);
        progress_bar.step("Applying Sobel filters...");
        Matrix gradient_x = sobel_filter_x.apply(smoothed);
        Matrix gradient_y = sobel_filter_y.apply(smoothed);
        progress_bar.step("Computing gradient magnitude and direction...");
        Matrix magnitude = Gradients::computeGradientMagnitude(gradient_x, gradient_y);
        Matrix direction = Gradients::computeGradientDirection(gradient_x, gradient_y);
        progress_bar.step("Applying non-maximum suppression...");
        Matrix suppressed = non_max_suppression.apply(magnitude, direction);
        progress_bar.step("Applying thresholding...");
        Matrix thresholded = applyThreshold(suppressed);
        progress_bar.step("Tracking edges...");
        Matrix edges = trackEdges(thresholded);
        return edges;
    }

    Matrix Canny::applyThreshold(const Matrix &image)
    {
        // Create a new matrix of the same size as the input, initialized to 0
        Matrix thresholded = Matrix::zeros(image.rows, image.cols);

        for (int i = 0; i < image.rows; i++)
        {
            for (int j = 0; j < image.cols; j++)
            {
                if (image.get(i, j) > high_threshold)
                {
                    thresholded.set(i, j, 255);  // Strong edge
                }
                else if (image.get(i, j) > low_threshold)
                {
                    thresholded.set(i, j, 128);  // Weak edge
                }
                // else: thresholded[i][j] = 0;  // No edge
            }
        }

        return thresholded;
    }

    Matrix Canny::trackEdges(const Matrix &image)
    {
        Matrix edges = Matrix::zeros(image.rows, image.cols);

        for (int i = 1; i < image.rows - 1; i++)
        {
            for (int j = 1; j < image.cols - 1; j++)
            {
                if (image.get(i, j) == 255)
                {
                    edges.set(i, j, 255); // Strong edge
                }
                // If the pixel is a weak edge but has a strong edge in its 8-connected neighborhood, set it in the output image
                else if (image.get(i, j) == 128)
                {
                    if ((image.get(i - 1, j - 1) == 255) || (image.get(i - 1, j) == 255) || (image.get(i - 1, j + 1) == 255) ||
                        (image.get(i, j - 1) == 255) || (image.get(i, j + 1) == 255) ||
                        (image.get(i + 1, j - 1) == 255) || (image.get(i + 1, j) == 255) || (image.get(i + 1, j + 1) == 255))
                    {
                        edges.set(i, j, 255);
                    }
                }
            }
        }

        return edges;
    }

}
