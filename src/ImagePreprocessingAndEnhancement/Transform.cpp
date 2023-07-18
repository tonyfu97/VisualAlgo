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

    // Translation
    Matrix Transform::translate(const Matrix &image, int dx, int dy, InterpolationType method)
    {
        return affine(image, translate(dx, dy), method);
    }

    Matrix Transform::translate(int dx, int dy)
    {
        return Matrix({{1, 0, static_cast<float>(dx)},
                       {0, 1, static_cast<float>(dy)},
                       {0, 0, 1}});
    }

    // Scaling
    Matrix Transform::scale(const Matrix &image, float sx, float sy, InterpolationType method)
    {
        return affine(image, scale(sx, sy), method);
    }

    Matrix Transform::scale(float sx, float sy)
    {
        return Matrix({{sx, 0, 0},
                       {0, sy, 0},
                       {0, 0, 1}});
    }

    // Rotation
    Matrix Transform::rotate(const Matrix &image, float angle, InterpolationType method)
    {
        return affine(image, rotate(angle), method);
    }

    Matrix Transform::rotate(float angle)
    {
        return Matrix({{std::cos(angle), -std::sin(angle), 0},
                       {std::sin(angle), std::cos(angle), 0},
                       {0, 0, 1}});
    }

    // Shear
    Matrix Transform::shear(const Matrix &image, float kx, float ky, InterpolationType method)
    {
        return affine(image, shear(kx, ky), method);
    }

    Matrix Transform::shear(float kx, float ky)
    {
        if (kx == 1.0f && ky == 1.0f)
        {
            throw std::invalid_argument("Shearing factors kx and ky cannot both be 1, as this would lead to a singular transformation matrix, i.e., the image will collapse into a single line.");
        }
        return Matrix({{1, kx, 0},
                       {ky, 1, 0},
                       {0, 0, 1}});
    }

    // Affine Transformation
    Matrix Transform::affine(const Matrix &image, const Matrix &transform_matrix, InterpolationType method)
    {
        auto [center_x, center_y] = center_coords(image);
        Matrix translation_to_center = Transform::translate(-center_x, -center_y);
        Matrix translation_to_origin = Transform::translate(center_x, center_y);

        Matrix inverse_transform_matrix = transform_matrix.inverse();

        Matrix transformed_image = Matrix::zeros(image.rows, image.cols);

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

    // Perspective Transformation
    Matrix Transform::perspective(const Matrix &image, const Matrix &transform_matrix, InterpolationType method)
    {
        auto [center_x, center_y] = center_coords(image);
        Matrix translation_to_center = Transform::translate(-center_x, -center_y);
        Matrix translation_to_origin = Transform::translate(center_x, center_y);

        Matrix inverse_transform_matrix = transform_matrix.inverse();

        Matrix transformed_image = Matrix::zeros(image.rows, image.cols);

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
                float transformed_z = transformed_point.get(2, 0);

                if (transformed_z < 0)  // Behind the camera, should not be visible
                {
                    transformed_image.set(y, x, 0);
                    continue;
                }
                
                transformed_image.set(y, x, Interpolate::interpolate(image, transformed_x / transformed_z, transformed_y / transformed_z, method, 0));
            }
        }

        return transformed_image;
    }

    // Private Helper Functions
    std::pair<float, float> Transform::center_coords(const Matrix &image)
    {
        return {static_cast<float>(image.cols - 1) / 2, static_cast<float>(image.rows - 1) / 2};
    }
}
