#pragma once

#include "helpers/Matrix.hpp"

namespace VisualAlgo::FeatureExtraction
{

    class Filter
    {
    public:
        virtual Matrix apply(const Matrix &image) const = 0;

    protected:
        Matrix kernel;
    };

    class GaussianFilter : public Filter
    {
    public:
        GaussianFilter(float sigma);
        virtual Matrix apply(const Matrix &image) const override;

    private:
        float sigma;
        Matrix computeGaussianKernel(float sigma) const;
    };

    class SobelFilterX : public Filter
    {
    public:
        SobelFilterX();
        virtual Matrix apply(const Matrix &image) const override;

    private:
        Matrix sobelX = Matrix({{1, 0, -1},
                                {2, 0, -2},
                                {1, 0, -1}});
    };

    class SobelFilterY : public Filter
    {
    public:
        SobelFilterY();
        virtual Matrix apply(const Matrix &image) const override;

    private:
        Matrix sobelY = Matrix({{1, 2, 1},
                                {0, 0, 0},
                                {-1, -2, -1}});
    };

    // TODO: add more filters as needed
}
