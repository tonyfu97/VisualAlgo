#include "Transform.hpp"
#include "Interpolate.hpp"
#include "helpers/Matrix.hpp"

#include <cmath>

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    Matrix Transform::translate(const Matrix &image, int dx, int dy, InterpolationType method)
    {
        Matrix transform_matrix = Matrix::eye(3, 3);
        transform_matrix.set(0, 2, dx);
        transform_matrix.set(1, 2, dy);

        return affine(image, transform_matrix, method);
    }

    Matrix Transform::scale(const Matrix &image, float sx, float sy, InterpolationType method)
    {
        Matrix transform_matrix = Matrix::eye(3, 3);
        transform_matrix.set(0, 0, sx);
        transform_matrix.set(1, 1, sy);

        return affine(image, transform_matrix, method);
    }

    Matrix Transform::rotate(const Matrix &image, float angle, InterpolationType method)
    {
        Matrix transform_matrix = Matrix::eye(3, 3);
        transform_matrix.set(0, 0, std::cos(angle));
        transform_matrix.set(0, 1, -std::sin(angle));
        transform_matrix.set(1, 0, std::sin(angle));
        transform_matrix.set(1, 1, std::cos(angle));

        return affine(image, transform_matrix, method);
    }

    Matrix Transform::shear(const Matrix &image, float kx, float ky, InterpolationType method)
    {
        Matrix transform_matrix = Matrix::eye(3, 3);
        transform_matrix.set(0, 1, kx);
        transform_matrix.set(1, 0, ky);

        return affine(image, transform_matrix, method);
    }

    Matrix Transform::affine(const Matrix &image, const Matrix &transform_matrix, InterpolationType method)
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

                transformed_image.set(y, x, Interpolate::interpolate(image, transformed_x, transformed_y, method));
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

                Matrix transformed_point = inverse_transform_matrix * point;

                float transformed_x = transformed_point.get(0, 0);
                float transformed_y = transformed_point.get(1, 0);
                float transformed_z = transformed_point.get(2, 0);

                transformed_image.set(y, x, Interpolate::interpolate(image, transformed_x / transformed_z, transformed_y / transformed_z, method));
            }
        }

        return transformed_image;
    }

}