#pragma once

#include "helpers/Matrix.hpp"

namespace VisualAlgo::SegmentationAndGrouping
{

    class Thresholding
    {
    public:
        // Binary thresholding
        static Matrix apply(const Matrix &img, float threshold);
    };

}
