#include "TestHarness.h"
#include "helpers/matrix.hpp"
#include "helpers/stimulus.hpp"
#include "SegmentationAndGrouping/FBF.hpp"

using namespace VisualAlgo;

void test_mondrian1()
{
    // Matrix input = Stimulus::random_mondrian(256, 256, 6);
    Matrix input = Matrix::load("datasets/SegmentationAndGrouping/car_moon_noisy.ppm", 256, 256);
    input /= input.max();
    Stimulus::add_noise(input, 0.1);
    input.save("results/SegmentationAndGrouping/FBF/mondrian1_input.ppm", true);

    SegmentationAndGrouping::FBF fbf;
    fbf.set_debug_dir("results/SegmentationAndGrouping/FBF/");
    Matrix output = fbf.apply(input);
}
    

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);

    // test_mondrian1();

    return 0;
}
