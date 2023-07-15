#pragma once

#include "helpers/Matrix.hpp"

#include <map>
#include <vector>
#include <tuple>

namespace VisualAlgo::FeatureExtraction
{

    class Blob
    {
    public:
        virtual ~Blob() {}

        virtual Matrix apply(const Matrix &image) const = 0;
        virtual std::vector<std::tuple<int, int, float>> detect(const Matrix &image) const = 0;

    protected:
        std::vector<std::tuple<int, int, float>> findLocalMaxima(const std::vector<Matrix> &scale_space, const std::vector<float> &sigmas, int window_size, float threshold) const;
    };

    class BlobDoG : public Blob
    {
    public:
        BlobDoG(float initial_sigma, float k, float threshold, int window_size, int octaves);
        Matrix apply(const Matrix &image) const override;
        std::vector<std::tuple<int, int, float>> detect(const Matrix &image) const override;

    private:
        float initial_sigma;
        float k;
        float threshold;
        int window_size;
        int octaves;
    };

    class BlobLoG : public Blob
    {
    public:
        BlobLoG(float initial_sigma, float k, float threshold, int window_size, int octaves);
        Matrix apply(const Matrix &image) const override;
        std::vector<std::tuple<int, int, float>> detect(const Matrix &image) const override;

    private:
        float initial_sigma;
        float k;
        float threshold;
        int window_size;
        int octaves;
    };

    // TODO: Add additional blob detector classes as needed.
}