#pragma once

#include "helpers/Matrix.hpp"
#include "Interpolate.hpp"

#include <utility>
#include <string>

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    class Transform
    {
    public:
        // Translation
        static Matrix translate(const Matrix &image, int dx, int dy, InterpolationType method = InterpolationType::NEAREST);

        static Matrix translate(int dx, int dy);

        // Scaling
        static Matrix scale(const Matrix &image, float sx, float sy, InterpolationType method = InterpolationType::NEAREST);

        static Matrix scale(float sx, float sy);

        // Rotation
        static Matrix rotate(const Matrix &image, float angle, InterpolationType method = InterpolationType::NEAREST);

        static Matrix rotate(float angle);

        // Shear
        static Matrix shear(const Matrix &image, float kx, float ky, InterpolationType method = InterpolationType::NEAREST);

        static Matrix shear(float kx, float ky);

        // Affine Transformation
        static Matrix affine(const Matrix &image, const Matrix &transform_matrix, InterpolationType method = InterpolationType::NEAREST);

        // Perspective Transformation
        static Matrix perspective(const Matrix &image, const Matrix &transform_matrix, InterpolationType method = InterpolationType::NEAREST);

    private:
        static std::pair<float, float> center_coords(const Matrix &image);
    };

}
