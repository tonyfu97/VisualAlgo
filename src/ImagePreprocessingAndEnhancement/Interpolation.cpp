#include "Interpolation.hpp"
#include "helpers/Matrix.hpp"

#include <cmath>
#include <stdexcept>
#include <string>
#include <algorithm>

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    std::string to_string(InterpolationType type)
    {
        switch (type)
        {
        case InterpolationType::NEAREST:
            return "nearest";
        case InterpolationType::BILINEAR:
            return "bilinear";
        case InterpolationType::BICUBIC:
            return "bicubic";
        default:
            return "unknown";
        }
    }

    float Interpolation::nearest(const Matrix &image, float x, float y)
    {
        int x_rounded = static_cast<int>(std::round(x));
        int y_rounded = static_cast<int>(std::round(y));

        x_rounded = std::clamp(x_rounded, 0, image.cols - 1);
        y_rounded = std::clamp(y_rounded, 0, image.rows - 1);

        return image.get(y_rounded, x_rounded);
    }

    float Interpolation::bilinear(const Matrix &image, float x, float y)
    {
        int x1 = static_cast<int>(std::floor(x));
        int y1 = static_cast<int>(std::floor(y));
        int x2 = x1 + 1;
        int y2 = y1 + 1;

        x1 = std::clamp(x1, 0, image.cols - 1);
        y1 = std::clamp(y1, 0, image.rows - 1);
        x2 = std::clamp(x2, 0, image.cols - 1);
        y2 = std::clamp(y2, 0, image.rows - 1);

        if (x1 == x2 && y1 == y2)
        {
            return image.get(y1, x1);
        }

        float q11 = image.get(y1, x1);
        float q12 = image.get(y1, x2);
        float q21 = image.get(y2, x1);
        float q22 = image.get(y2, x2);

        float x2x = x2 - x;
        float xx1 = x - x1;
        float y2y = y2 - y;
        float yy1 = y - y1;

        float r1 = q11 * x2x + q12 * xx1;
        float r2 = q21 * x2x + q22 * xx1;

        return r1 * y2y + r2 * yy1;
    }

    // One dimensional: ax^3 + bx^2 + cx + d
    float Interpolation::cubicInterpolation(float p[4], float x)
    {
        return p[1] + 0.5 * x * (p[2] - p[0] + 2.0 * x * (2.0 * p[0] - 5.0 * p[1] + 4.0 * p[2] - p[3] + x * (3.0 * (p[1] - p[2]) + p[3] - p[0])));
    }

    // Simplified implementation: no color, no handling of edge cases, not optimized.
    float Interpolation::bicubic(const Matrix &image, float x, float y)
    {
        int xInt = static_cast<int>(std::round(x));
        int yInt = static_cast<int>(std::round(y));
        float xFrac = x - xInt;
        float yFrac = y - yInt;

        float interpolatedCol[4];
        for (int i = 0; i < 4; i++)
        {
            float p[4];
            for (int j = 0; j < 4; j++)
            {
                int xIndex = std::clamp(xInt - 1 + j, 0, image.cols - 1);
                int yIndex = std::clamp(yInt - 1 + i, 0, image.rows - 1);
                p[j] = image.get(yIndex, xIndex);
            }
            interpolatedCol[i] = cubicInterpolation(p, xFrac);
        }
        return cubicInterpolation(interpolatedCol, yFrac);
    }

    float Interpolation::interpolate(const Matrix &image, float x, float y, InterpolationType type)
    {
        switch (type)
        {
        case InterpolationType::NEAREST:
            return nearest(image, x, y);
        case InterpolationType::BILINEAR:
            return bilinear(image, x, y);
        case InterpolationType::BICUBIC:
            return bicubic(image, x, y);
        default:
            throw std::invalid_argument("Invalid interpolation type: " + std::to_string((int)type) + ".");
        }
    }

    Matrix Interpolation::interpolate(const Matrix &image, float scale, InterpolationType type)
    {
        int rows = static_cast<int>(std::round(image.rows * scale));
        int cols = static_cast<int>(std::round(image.cols * scale));

        return interpolate(image, rows, cols, type);
    }

    Matrix Interpolation::interpolate(const Matrix &image, int rows, int cols, InterpolationType type)
    {
        Matrix result(rows, cols);

        float x_ratio = static_cast<float>(image.cols - 1) / static_cast<float>(cols);
        float y_ratio = static_cast<float>(image.rows - 1) / static_cast<float>(rows);

        for (int i = 0; i < rows; i++)
        {
            float y = i * y_ratio;
            for (int j = 0; j < cols; j++)
            {
                float x = j * x_ratio;
                result.set(i, j, interpolate(image, x, y, type));
            }
        }

        return result;
    }

}
