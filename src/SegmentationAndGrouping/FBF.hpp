#pragma once

#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>

#include "helpers/Matrix.hpp"

#define DEBUG 1

namespace VisualAlgo::SegmentationAndGrouping
{
    struct ShuntingCell
    {
        float A = 134;
        float B = 1;
        float C = 7;
        float D = 0.5;
        float E = 3.333;
        float ALPHA = 1.3;
        float BETA = 1.875;
        const int KERNEL_SIZE = 10;

        ShuntingCell();

        virtual Matrix apply(Matrix input) = 0; // Pure virtual function
    };

    struct ShuntingOnCell : public ShuntingCell
    {
        Matrix apply(Matrix input) override;
    };

    struct ShuntingOffCell : public ShuntingCell
    {
        float S = 0.2;

        Matrix apply(Matrix input) override;
    };

    struct SimpleCell
    {
        float theta;  // in radians
        int scale;    // 1 or 2
        bool is_left; // Why is this necessary? Can't we just use theta?
        int major_axis, minor_axis;
        float alpha;        // threshold contrast parameter
        float beta = 0.012; // threshold noise parameter

        SimpleCell(float theta, int scale, bool is_left);

        Matrix apply(Matrix input);
    };

    struct ComplexCell
    {
        float F = 0.5;

        ComplexCell();

        Matrix apply(Matrix simple_on_l, Matrix simple_on_r, Matrix simple_off_l, Matrix simple_off_r);
    };

    struct HypercomplexCellFirstCompetitiveStage
    {
        const int scale;
        const float EPSILON = 0.1;
        const float MU = 0.1;
        const float TAU = 0.1;
        const float THETA_INCREMENT = M_PI / 8;

        HypercomplexCellFirstCompetitiveStage(int scale);

        VisualAlgo::Matrix oriented_competition_kernel(float theta);

        std::vector<Matrix> apply(const std::vector<Matrix> &complex_cells);
    };

    class FBF
    {
    public:
        FBF();
        ~FBF();

        void set_debug_dir(std::string dir);
        Matrix apply(Matrix input);

    private:
        const float THETA_INCREMENT = M_PI / 8;
        std::string debug_dir = "";
    };
}
