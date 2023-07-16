#pragma once

#include "helpers/Matrix.hpp"

#include <cmath>
#include <stdexcept>
#include <string>

// Function to calculate the proportion of pixels with absolute difference greater than tolerance
static float proportionAbsDiffExceedTol(const VisualAlgo::Matrix& m1, const VisualAlgo::Matrix& m2, float tol=0.01f)
{
    VisualAlgo::Matrix m1Norm = m1;
    VisualAlgo::Matrix m2Norm = m2;   
    m1Norm.normalize();
    m2Norm.normalize();

    if (m1Norm.rows != m2Norm.rows || m1Norm.cols != m2Norm.cols)
        throw std::invalid_argument("Matrix dimensions: " + std::to_string(m1Norm.rows) + "x" + std::to_string(m1Norm.cols) + " and " + std::to_string(m2Norm.rows) + "x" + std::to_string(m2Norm.cols) + " do not match.");

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
