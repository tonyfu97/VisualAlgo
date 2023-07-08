#pragma once

#include "helpers/matrix.hpp"

#include <cmath>
#include <string>

namespace VisualAlgo::SegmentationAndGrouping
{
    class FBF
    {
    public:
        FBF();
        ~FBF();

        void set_debug_dir(std::string dir);
        Matrix apply(Matrix input); 

    private:
        const float THETA_INCREMENT = M_PI / 8;
        std::string debug_dir = "";
    };
}
