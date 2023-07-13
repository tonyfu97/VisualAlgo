#pragma once

#include "helpers/Matrix.hpp"

#include <cmath>

// Function to calculate the proportion of pixels with absolute difference greater than tolerance
static float proportionAbsDiffExceedTol(const VisualAlgo::Matrix& m1, const VisualAlgo::Matrix& m2, float tol=0.01f)
{
    VisualAlgo::Matrix m1Norm = m1;
    VisualAlgo::Matrix m2Norm = m2;   
    m1Norm.normalize();
    m2Norm.normalize();

    int count = 0;
    for (int i = 0; i < m1Norm.rows; i++)
    {
        for (int j = 0; j < m1Norm.cols; j++)
        {
            if (std::abs(m1Norm.get(i, j) - m2Norm.get(i, j)) > tol)
            {
                count++;
            }
        }
    }
    float proportion = static_cast<float>(count) / (m1Norm.rows * m1Norm.cols);
    return proportion;
}
