#include "Transform.hpp"
#include "Interpolate.hpp"
#include "helpers/Matrix.hpp"

#include <cmath>
#include <stdexcept>
#include <string>
#include <limits>
#include <utility>

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{
    std::string to_string(OutputSizeMode mode)
    {
        switch (mode)
        {
        case OutputSizeMode::Original:
            return "original";
        case OutputSizeMode::Fit:
            return "fit";
        case OutputSizeMode::Expand:
            return "expand";
        default:
            return "unknown";
        }
    }

    // Translation
    Matrix Transform::translate(const Matrix &image, int dx, int dy, InterpolationType method, OutputSizeMode sizeMode)
    {
        return affine(image, translate(dx, dy), method, sizeMode);
    }

    Matrix Transform::translate(int dx, int dy)
    {
        return Matrix({{1, 0, static_cast<float>(dx)},
                       {0, 1, static_cast<float>(dy)},
                       {0, 0, 1}});
    }

    // Scaling
    Matrix Transform::scale(const Matrix &image, float sx, float sy, InterpolationType method, OutputSizeMode sizeMode)
    {
        return affine(image, scale(sx, sy), method, sizeMode);
    }

    Matrix Transform::scale(float sx, float sy)
    {
        return Matrix({{sx, 0, 0},
                       {0, sy, 0},
                       {0, 0, 1}});
    }

    // Rotation
    Matrix Transform::rotate(const Matrix &image, float angle, InterpolationType method, OutputSizeMode sizeMode)
    {
        return affine(image, rotate(angle), method, sizeMode);
    }

    Matrix Transform::rotate(float angle)
    {
        return Matrix({{std::cos(angle), -std::sin(angle), 0},
                       {std::sin(angle), std::cos(angle), 0},
                       {0, 0, 1}});
    }

    // Shear
    Matrix Transform::shear(const Matrix &image, float kx, float ky, InterpolationType method, OutputSizeMode sizeMode)
    {
        return affine(image, shear(kx, ky), method, sizeMode);
    }

    Matrix Transform::shear(float kx, float ky)
    {
        return Matrix({{1, kx, 0},
                       {ky, 1, 0},
                       {0, 0, 1}});
    }

    // Affine Transformation
    Matrix Transform::calculateTransformedCorners(const Matrix &transform_matrix, const Matrix &image)
    {
        Matrix corners({{0, 0, 1},
                        {static_cast<float>(image.cols), 0, 1},
                        {0, static_cast<float>(image.rows), 1},
                        {static_cast<float>(image.cols), static_cast<float>(image.rows), 1}});

        return corners.matmul(transform_matrix.transpose());
    }

    std::pair<float, float> Transform::findMinMax(const Matrix &transformed_corners, int index)
    {
        float min_val = std::numeric_limits<float>::max();
        float max_val = std::numeric_limits<float>::min();

        for (int i = 0; i < 4; i++)
        {
            float val = transformed_corners.get(i, index);
            min_val = std::min(min_val, val);
            max_val = std::max(max_val, val);
        }

        return {min_val, max_val};
    }

    Matrix Transform::affine(const Matrix &image, const Matrix &transform_matrix, InterpolationType method, OutputSizeMode sizeMode)
    {
        auto [center_x, center_y] = center_coords(image);
        Matrix translation_to_center = Transform::translate(-center_x, -center_y);
        Matrix translation_to_origin = Transform::translate(center_x, center_y);

        Matrix scaled_transform_matrix = transform_matrix;
        int outputRows, outputCols;

        if (sizeMode != OutputSizeMode::Original)
        {
            Matrix transformed_corners = calculateTransformedCorners(scaled_transform_matrix, image);
            auto [min_x, max_x] = findMinMax(transformed_corners, 0);
            auto [min_y, max_y] = findMinMax(transformed_corners, 1);

            float new_width = max_x - min_x;
            float new_height = max_y - min_y;

            if (sizeMode == OutputSizeMode::Fit)
            {
                float scale_x = image.cols / new_width;
                float scale_y = image.rows / new_height;
                scaled_transform_matrix = Transform::scale(scale_x, scale_y).matmul(scaled_transform_matrix);

                outputRows = image.rows;
                outputCols = image.cols;
            }
            else if (sizeMode == OutputSizeMode::Expand)
            {
                outputRows = static_cast<int>(std::ceil(max_y - min_y));
                outputCols = static_cast<int>(std::ceil(max_x - min_x));
            }
            else
            {
                throw std::invalid_argument("OutputSizeMode: " + std::to_string(static_cast<int>(sizeMode)) + " is not supported.");
            }
        }
        else
        {
            outputRows = image.rows;
            outputCols = image.cols;
        }

        Matrix inverse_transform_matrix = scaled_transform_matrix.inverse();
        Matrix transformed_image = Matrix::zeros(outputRows, outputCols);

        for (int y = 0; y < transformed_image.rows; y++)
        {
            for (int x = 0; x < transformed_image.cols; x++)
            {
                Matrix point = Matrix::ones(3, 1);
                point.set(0, 0, x);
                point.set(1, 0, y);

                Matrix point_in_center = translation_to_center.matmul(point);
                Matrix transformed_point_in_center = inverse_transform_matrix.matmul(point_in_center);
                Matrix transformed_point = translation_to_origin.matmul(transformed_point_in_center);

                float transformed_x = transformed_point.get(0, 0);
                float transformed_y = transformed_point.get(1, 0);

                transformed_image.set(y, x, Interpolate::interpolate(image, transformed_x, transformed_y, method, 0));
            }
        }

        return transformed_image;
    }

    Matrix Transform::perspective(const Matrix &image, const Matrix &transform_matrix, InterpolationType method)
    {
        Matrix inverse_transform_matrix = transform_matrix.inverse();

        Matrix transformed_image = Matrix::zeros(image.rows, image.cols);

        for (int y = 0; y < transformed_image.rows; y++)
        {
            for (int x = 0; x < transformed_image.cols; x++)
            {
                Matrix point = Matrix::ones(3, 1);
                point.set(0, 0, x);
                point.set(1, 0, y);

                Matrix transformed_point = inverse_transform_matrix.matmul(point);

                float transformed_x = transformed_point.get(0, 0);
                float transformed_y = transformed_point.get(1, 0);
                float transformed_z = transformed_point.get(2, 0);

                transformed_image.set(y, x, Interpolate::interpolate(image, transformed_x / transformed_z, transformed_y / transformed_z, method, 0));
            }
        }

        return transformed_image;
    }

    std::pair<float, float> Transform::center_coords(const Matrix &image)
    {
        return {static_cast<float>(image.cols - 1) / 2, static_cast<float>(image.rows - 1) / 2};
    }
}
