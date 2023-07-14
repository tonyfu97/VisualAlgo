#pragma once

#include "helpers/Matrix.hpp"
#include "Gradients.hpp"
#include "Filter.hpp"

namespace VisualAlgo::FeatureExtraction
{

    class Harris
    {
    public:
        Harris(float sigma, float k, float threshold);

        Matrix apply(const Matrix &image) const;
        static std::vector<std::pair<int, int>> detect(const Matrix &image, float sigma, float k, float threshold);
    private:
        float sigma, k, threshold;
    };

}
