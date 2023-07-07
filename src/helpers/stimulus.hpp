#pragma once

#include "matrix.hpp"

namespace VisualAlgo::Stimulus
{
    Matrix random_mondrian(int rows, int cols, int num_rectangles);
    void add_noise(Matrix &matrix, float noise_probability);
}
