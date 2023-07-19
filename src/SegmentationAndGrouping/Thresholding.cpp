#include "SegmentationAndGrouping/Thresholding.hpp"
#include "helpers/Matrix.hpp"

namespace VisualAlgo::SegmentationAndGrouping
{

    Matrix Thresholding::apply(const Matrix &img, float threshold)
    {
        Matrix result = img;

        for (int i = 0; i < img.rows; ++i)
        {
            for (int j = 0; j < img.cols; ++j)
            {
                if (img.get(i, j) > threshold)
                    result.set(i, j, 255); // foreground
                else
                    result.set(i, j, 0); // background
            }
        }

        return result;
    }

}
