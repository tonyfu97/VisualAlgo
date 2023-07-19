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

    class LoGFilter : public Filter
    {
    public:
        LoGFilter(float sigma);
        virtual Matrix apply(const Matrix &image) const override;
    private:
        float sigma;
        Matrix kernel;
        Matrix computeLoGKernel(float sigma) const;
    };

    class MedianFilter : public Filter
    {
    public:
        MedianFilter(int size);
        virtual Matrix apply(const Matrix &image) const override;

    private:
        int size;
        float compute_median(const Matrix &image, int row, int col, int size) const;
    };

    // TODO: add more filters as needed
}
