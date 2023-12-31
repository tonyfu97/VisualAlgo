#pragma once

#include "helpers/Matrix.hpp"

#include <string>

namespace VisualAlgo::ImagePreprocessingAndEnhancement
{

    enum class InterpolationType
    {
        NEAREST,
        BILINEAR,
        BICUBIC
    };

    std::string to_string(InterpolationType type);

    class Interpolate
    {
    public:
        static float nearest(const Matrix &image, float x, float y);
        static float bilinear(const Matrix &image, float x, float y);
        static float bicubic(const Matrix &image, float x, float y);

        static float interpolate(const Matrix &image, float x, float y, InterpolationType type);
        static float interpolate(const Matrix &image, float x, float y, InterpolationType type, float default_value);
        static Matrix interpolate(const Matrix &image, float scale, InterpolationType type);
        static Matrix interpolate(const Matrix &image, int rows, int cols, InterpolationType type);

    private:
        static float cubicInterpolation(float p[4], float x);
    };
}
