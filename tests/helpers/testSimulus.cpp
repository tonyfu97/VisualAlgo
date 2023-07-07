#include "TestHarness.h"
#include "helpers/stimulus.hpp"

namespace VisualAlgo::Stimulus
{
    TEST(random_mondrian, random_mondrian)
    {
        Matrix matrix = random_mondrian(10, 10, 10);
        CHECK_EQUAL(matrix.rows, 10);
        CHECK_EQUAL(matrix.cols, 10);
        matrix.save("results/helpers/stimulus/random_mondrian_test1.ppm", true);
    }

    TEST(add_noise, add_noise)
    {
        Matrix matrix = random_mondrian(10, 10, 10);
        matrix.save("results/helpers/stimulus/without_noise_test1.ppm", true);
        add_noise(matrix, 0.1);
        CHECK_EQUAL(matrix.rows, 10);
        CHECK_EQUAL(matrix.cols, 10);
        matrix.save("results/helpers/stimulus/add_noise_test1.ppm", true);
    }
}