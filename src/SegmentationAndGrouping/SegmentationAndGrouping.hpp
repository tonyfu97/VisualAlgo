#pragma once

#include "helpers/matrix.hpp"

#include <cmath>

namespace VisualAlgo::SegmentationAndGrouping
{
    class FBF
    {
    public:
        FBF();
        ~FBF();

        Matrix apply(Matrix input); 

    private:
        float THETA_INCREMENT = M_PI / 8;
    };
}
