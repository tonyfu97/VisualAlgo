#pragma once

#include "helpers/matrix.hpp"

namespace VisualAlgo::SegmentationAndGrouping
{
    class FBF
    {
    public:
        FBF();
        ~FBF();

        Matrix apply(Matrix input); 

    private:
        float A, B, C, D, E, S, ALPHA, BETA;
    };
}
