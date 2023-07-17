#pragma once

#include "helpers/Matrix.hpp"
#include "Interpolation.hpp"

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    class Transform
    {
    public:
        // Translation
        static Matrix translate(const Matrix &image, int dx, int dy, InterpolationType method = InterpolationType::NEAREST);

        // Scaling
        static Matrix scale(const Matrix &image, float sx, float sy, InterpolationType method = InterpolationType::NEAREST);

        // Rotation
        static Matrix rotate(const Matrix &image, float angle, InterpolationType method = InterpolationType::NEAREST);

        // Shear
        static Matrix shear(const Matrix &image, float kx, float ky, InterpolationType method = InterpolationType::NEAREST);

        // Affine Transformation
        static Matrix affine(const Matrix &image, const Matrix &transform_matrix, InterpolationType method = InterpolationType::NEAREST);

        // Perspective Transformation
        static Matrix perspective(const Matrix &image, const Matrix &transform_matrix, InterpolationType method = InterpolationType::NEAREST);
    };

}
