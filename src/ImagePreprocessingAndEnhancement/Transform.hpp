#pragma once

#include "helpers/Matrix.hpp"
#include "Interpolate.hpp"

#include <utility>
#include <string>

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{
    enum class OutputSizeMode
    {
        // All modes are non-distorting.
        Original, // The output matrix is the same size as the input image. Transformations may cause some pixels to fall outside of the output image.
        Fit,      // The output matrix is the same size as the input image. Transformations are adjusted so that all pixels fall within the output image.
        Expand,   // The output matrix dimensions are adjusted so all transformed pixels fit within the image (may be larger or smaller than the original). The extra space can be filled with a default value like zero, typically resulting in a black padding.
    };

    std::string to_string(OutputSizeMode mode);

    class Transform
    {
    public:
        // Translation
        static Matrix translate(const Matrix &image, int dx, int dy, InterpolationType method = InterpolationType::NEAREST, OutputSizeMode sizeMode = OutputSizeMode::Original);

        static Matrix translate(int dx, int dy);

        // Scaling
        static Matrix scale(const Matrix &image, float sx, float sy, InterpolationType method = InterpolationType::NEAREST, OutputSizeMode sizeMode = OutputSizeMode::Original);

        static Matrix scale(float sx, float sy);

        // Rotation
        static Matrix rotate(const Matrix &image, float angle, InterpolationType method = InterpolationType::NEAREST, OutputSizeMode sizeMode = OutputSizeMode::Original);

        static Matrix rotate(float angle);

        // Shear
        static Matrix shear(const Matrix &image, float kx, float ky, InterpolationType method = InterpolationType::NEAREST, OutputSizeMode sizeMode = OutputSizeMode::Original);

        static Matrix shear(float kx, float ky);

        // Affine Transformation
        static Matrix affine(const Matrix &image, const Matrix &transform_matrix, InterpolationType method = InterpolationType::NEAREST, OutputSizeMode sizeMode = OutputSizeMode::Original);

        // Perspective Transformation (currently only supports OutputSizeMode::Original)
        static Matrix perspective(const Matrix &image, const Matrix &transform_matrix, InterpolationType method = InterpolationType::NEAREST);

    private:
        static std::pair<float, float> center_coords(const Matrix &image);

        // Affine Transformation Helpers
        static Matrix calculateTransformedCorners(const Matrix &transform_matrix, const Matrix &image);
        static std::pair<float, float> findMinMax(const Matrix &corners, int index);
    };

}
