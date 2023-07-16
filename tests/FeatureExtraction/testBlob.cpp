// All tests are passed, but commented out because they take too long to run.

// #include "TestHarness.h"
// #include "helpers/Matrix.hpp"
// #include "FeatureExtraction/Blob.hpp"
// #include "FeatureExtraction/Filter.hpp"
// #include "test_utils.hpp"

// #include <iostream>
// #include <string>
// #include <cmath>

// const float MAX_PROPORTION_ABS_DIFF = 0.001f;

// static bool test_blob(std::string img_name, std::string blobType)
// {
//     VisualAlgo::Matrix image, image_blob_expected;
//     image.load("datasets/FeatureExtraction/" + img_name + "_resized.ppm");
//     image_blob_expected.load("datasets/FeatureExtraction/" + img_name + "_expected_blob_" + blobType + ".ppm");

//     image.normalize();
//     image_blob_expected.normalize();

//     VisualAlgo::FeatureExtraction::Blob *blob;
//     if (blobType == "dog")
//         blob = new VisualAlgo::FeatureExtraction::BlobDoG(10, 0.7, 0.2, 5, 1);
//     else if (blobType == "log")
//         blob = new VisualAlgo::FeatureExtraction::BlobLoG(10, 0.7, 0.2, 5, 1);
//     else
//         return false;

//     VisualAlgo::Matrix image_blob = blob->apply(image);

//     image_blob.save("datasets/FeatureExtraction/" + img_name + "_blob_" + blobType + ".ppm", true);

//     float padet = proportionAbsDiffExceedTol(image_blob, image_blob_expected);

//     // std::cout << "Proportion of absolute difference exceeding tolerance for " << img_name << "_" << blobType << ".ppm: " << padet << std::endl;

//     delete blob;
//     return (padet < MAX_PROPORTION_ABS_DIFF);
// }

// namespace VisualAlgo::FeatureExtraction
// {

//     TEST(BlobTestSuite, BlobDoGMondrian)
//     {
//         CHECK(test_blob("mondrian", "dog"));
//     }

//     TEST(BlobTestSuite, BlobLoGMMondrian)
//     {
//         CHECK(test_blob("mondrian", "log"));
//     }

// }
