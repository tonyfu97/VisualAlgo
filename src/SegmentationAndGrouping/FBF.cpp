#include "SegmentationAndGrouping.hpp"
#include "helpers/matrix.hpp"

#include <cmath>
#include <stdexcept>
#include <vector>

// Grossberg and Wyse (1992) take the log inside of the exponential. This is not a standard gaussian function.
static float gaussian(float p, float q, float i, float j, float C_or_E, float alpha_or_beta)
{
    return C_or_E * exp(-pow(alpha_or_beta, -2) * log(2 * (p - i) * (p - i) + 2 * (q - j) * (q - j)));
}

static VisualAlgo::Matrix half_ellipse(int major_axis, int minor_axis, float theta, float fill_value = 1, bool is_left = true)
{
    VisualAlgo::Matrix matrix(major_axis, minor_axis, 0);
    float center_x = matrix.rows / 2;
    float center_y = matrix.cols / 2;
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            float x = i - center_x;
            float y = j - center_y;
            float rotated_x = x * cos(theta) - y * sin(theta);
            float rotated_y = x * sin(theta) + y * cos(theta);
            if ((rotated_x * rotated_x / (major_axis * major_axis) + rotated_y * rotated_y / (minor_axis * minor_axis) <= 1) &&
                ((is_left && rotated_y <= 0) || (!is_left && rotated_y >= 0)))
            {
                matrix.set(i, j, fill_value);
            }
        }
    }
    return matrix;
}

struct ShuntingOnCell
{
    float A = 134;
    float B = 1;
    float C = 7;
    float D = 0.5;
    float E = 3.333;
    float ALPHA = 1.3;
    float BETA = 1.875;
    const int KERNEL_SIZE = 10;

    ShuntingOnCell()
    {
    }

    VisualAlgo::Matrix apply(VisualAlgo::Matrix input)
    {
        VisualAlgo::Matrix output(input.rows, input.cols, 0);
        for (int i = 0; i < input.rows; i++)
        {
            for (int j = 0; j < input.cols; j++)
            {
                float numerator_sum = 0;
                float denominator_sum = A;
                for (int p = 0; p < KERNEL_SIZE; p++)
                {
                    for (int q = 0; q < KERNEL_SIZE; q++)
                    {
                        numerator_sum += input.get(i, j) * (B * gaussian(p, q, i, j, C, ALPHA) - D * gaussian(p, q, i, j, E, BETA));
                        denominator_sum += input.get(i, j) * (gaussian(p, q, i, j, C, ALPHA) + gaussian(p, q, i, j, E, BETA));
                    }
                }
                output[i][j] = numerator_sum / denominator_sum;
            }
        }
        return output;
    }
};

struct ShuntingOffCell
{
    float A = 134;
    float B = 1;
    float C = 7;
    float D = 0.5;
    float E = 3.333;
    float S = 0.2;
    float ALPHA = 1.3;
    float BETA = 1.875;
    const int KERNEL_SIZE = 10;

    ShuntingOffCell()
    {
    }

    VisualAlgo::Matrix apply(VisualAlgo::Matrix input)
    {
        VisualAlgo::Matrix output(input.rows, input.cols, 0);
        for (int i = 0; i < input.rows; i++)
        {
            for (int j = 0; j < input.cols; j++)
            {
                float numerator_sum = A * S;
                float denominator_sum = A;
                for (int p = 0; p < KERNEL_SIZE; p++)
                {
                    for (int q = 0; q < KERNEL_SIZE; q++)
                    {
                        numerator_sum += input.get(i, j) * (D * gaussian(p, q, i, j, E, BETA) - B * gaussian(p, q, i, j, C, ALPHA));
                        denominator_sum += input.get(i, j) * (gaussian(p, q, i, j, C, ALPHA) + gaussian(p, q, i, j, E, BETA));
                    }
                }
                output[i][j] = numerator_sum / denominator_sum - S;
            }
        }
        return output;
    }
};

struct SimpleCell
{
    float theta;  // in radians
    int scale;    // 1 or 2
    bool is_left; // Why is this necessary? Can't we just use theta?
    int major_axis, minor_axis;
    float alpha;        // threshold contrast parameter
    float beta = 0.012; // threshold noise parameter

    SimpleCell(float theta, int scale, bool is_left) : theta(theta), scale(scale), is_left(is_left)
    {
        switch (scale)
        {
        case 1:
            major_axis = 12;
            minor_axis = 6;
            alpha = 1.4;
            break;
        case 2:
            major_axis = 20;
            minor_axis = 10;
            alpha = 2.0;
            break;
        default:
            throw std::invalid_argument("Scale must be 1 or 2");
        }
    }

    VisualAlgo::Matrix apply(VisualAlgo::Matrix input)
    {
        // Precompute the kernels. There are two halves.
        VisualAlgo::Matrix L_kernel = half_ellipse(major_axis, minor_axis, theta, 1, true);
        VisualAlgo::Matrix R_kernel = half_ellipse(major_axis, minor_axis, theta, 1, false);
        VisualAlgo::Matrix whole_kernel;
        if (is_left)
        {
            whole_kernel = L_kernel - R_kernel * alpha - beta;
        }
        else
        {
            whole_kernel = R_kernel - L_kernel * alpha - beta;
        }

        // Normalize the kernel.
        whole_kernel /= whole_kernel.sum();

        // Cross correlate the kernels with the input.
        VisualAlgo::Matrix output = input.cross_correlation(whole_kernel, major_axis / 2, 1);

        // Rectify the output.
        output.relu();

        return output;
    }
};

struct ComplexCell
{
    float F = 0.5;

    ComplexCell()
    {
    }

    VisualAlgo::Matrix apply(VisualAlgo::Matrix simple_on_l,
                             VisualAlgo::Matrix simple_on_r,
                             VisualAlgo::Matrix simple_off_l,
                             VisualAlgo::Matrix simple_off_r)
    {
        VisualAlgo::Matrix output(simple_on_l.rows, simple_on_l.cols, 0);
        output = (simple_on_l + simple_on_r + simple_off_l + simple_off_r) * F;
        return output;
    }
};

struct HypercomplexCellFirstCompetitiveStage
{
    float EPSILON = 0.1;
    float MU = 5;
    float TAU = 0.1;

    HypercomplexCellFirstCompetitiveStage()
    {
    }

    VisualAlgo::Matrix apply(VisualAlgo::Matrix complex)
    {
        VisualAlgo::Matrix output(complex.rows, complex.cols, 0);
        for (int i = 0; i < complex.rows; i++)
        {
            for (int j = 0; j < complex.cols; j++)
            {
                float numerator_sum = 0;
                float denominator_sum = 0;
                for (int p = 0; p < complex.rows; p++)
                {
                    for (int q = 0; q < complex.cols; q++)
                    {
                        numerator_sum += complex.get(i, j) * exp(-pow((i - p) * (i - p) + (j - q) * (j - q), 2) / (2 * EPSILON * EPSILON));
                        denominator_sum += exp(-pow((i - p) * (i - p) + (j - q) * (j - q), 2) / (2 * EPSILON * EPSILON));
                    }
                }
                output[i][j] = numerator_sum / denominator_sum;
            }
        }
        return output;
    }
};

namespace VisualAlgo::SegmentationAndGrouping
{
    FBF::FBF()
    {
    }

    FBF::~FBF()
    {
    }

    Matrix FBF::apply(Matrix input)
    {
        // Step 1: Discounting the Illuminant using the Shunting On and Shunting Off Cells
        auto shunting_on_cell = ShuntingOnCell();
        auto shunting_off_cell = ShuntingOffCell();
        Matrix shunting_on_output = shunting_on_cell.apply(input);
        Matrix shunting_off_output = shunting_off_cell.apply(input);

        // Step 2: CORT-X 2 Filter
        std::vector<Matrix> complex_cells_scale_1;  // 8 orientations
        std::vector<Matrix> complex_cells_scale_2;  // 8 orientations
        for (int s = 1; s <= 2; s++)
        {
            for (int i = 0; i < 8; i++)
            {
                float theta = i * THETA_INCREMENT;
                // Step 2a: Simple Cells
                auto simple_on_l = SimpleCell(theta, s, true).apply(shunting_on_output);
                auto simple_on_r = SimpleCell(theta, s, false).apply(shunting_on_output);
                auto simple_off_l = SimpleCell(theta, s, true).apply(shunting_off_output);
                auto simple_off_r = SimpleCell(theta, s, false).apply(shunting_off_output);
                
                // Step 2b: Complex Cells
                if (s == 1)
                {  
                    complex_cells_scale_1.push_back(ComplexCell().apply(simple_on_l, simple_on_r, simple_off_l, simple_off_r));
                }
                else
                {
                    complex_cells_scale_2.push_back(ComplexCell().apply(simple_on_l, simple_on_r, simple_off_l, simple_off_r));
                }
            }
        }

        // Step 2c: Hypercomplex Cells (First Competitive Stage)
        // Each complex cell excites the hypercomplexcell with similar orientation and inhibits the hypercomplex cell with orthogonal orientation.
        


        // Step 2c: Hypercomplex Cells (Second Competitive Stage)

        // Step 2d: Multiple Scale Interaction: Boundary Localization and Noise Suppression

        // Step 2e: Long-Range Cooporation: Boundary Completion

        // CORT-X 2 Ouput

        // Step 3: Filling-In

        // Step 4: Figure-Ground Separation
        Matrix percept(input.rows, input.cols, 0);

        return percept;
    }
}