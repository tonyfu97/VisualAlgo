#pragma once

#include <opencv2/core.hpp>

namespace VisualAlgo::SegmentationAndGrouping
{
    class FBF
    {
    public:
        FBF(float A=134, float B=1, float C=7, float D=0.5, float E=3.333, float S=0.2, float ALPHA=1.3, float BETA=1.875);
        ~FBF();

        cv::Mat apply(cv::Mat& image);
    private:
        float A, B, C, D, E, S, ALPHA, BETA;
    };
}
