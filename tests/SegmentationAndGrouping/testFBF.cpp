#include "TestHarness.h"
#include "helpers/Matrix.hpp"
#include "helpers/Stimulus.hpp"
#include "SegmentationAndGrouping/FBF.hpp"

using namespace VisualAlgo;

// static void test_mondrian1()
// {
//     // Matrix input = Stimulus::random_mondrian(256, 256, 6);
//     Matrix input = Matrix::load("datasets/SegmentationAndGrouping/car_moon_noisy.ppm", 256, 256);
//     input /= input.max();
//     Stimulus::add_noise(input, 0.1);
//     input.save("results/SegmentationAndGrouping/FBF/mondrian1_input.ppm", true);

//     SegmentationAndGrouping::FBF fbf;
//     fbf.set_debug_dir("results/SegmentationAndGrouping/FBF/");
//     Matrix output = fbf.apply(input);
// }

// TEST(FBFTestSuite, FBFMondrian1)
// {
//     test_mondrian1();
//     // No assertions, just check the output image.
// }
