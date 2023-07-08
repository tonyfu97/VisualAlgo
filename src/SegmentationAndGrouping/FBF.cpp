#include "SegmentationAndGrouping.hpp"
#include "helpers/matrix.hpp"

#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>

// Grossberg and Wyse (1992) take the log inside of the exponential. This is not a standard gaussian function.
static float gaussian(float p, float q, float i, float j, float C_or_E, float alpha_or_beta)
{
    // return C_or_E * exp(-pow(alpha_or_beta, -2) * log(2 * (p - i) * (p - i) + 2 * (q - j) * (q - j)));
    // log(0) cause +inf. Let just use the standard gaussian function.
    return C_or_E * exp(-pow(alpha_or_beta, -2) * (2 * (p - i) * (p - i) + 2 * (q - j) * (q - j)));
}

static VisualAlgo::Matrix gaussian(int rows, int cols, float C_or_E, float alpha_or_beta)
{
    VisualAlgo::Matrix matrix(rows, cols, 0);
    float center_x = matrix.rows / 2;
    float center_y = matrix.cols / 2;
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            matrix.set(i, j, gaussian(i, j, center_x, center_y, C_or_E, alpha_or_beta));
        }
    }
    return matrix;
}

static VisualAlgo::Matrix half_ellipse(int major_axis, int minor_axis, float theta, float fill_value = 1, bool is_left = true)
{
    int KERNEL_SIZE = static_cast<int>(major_axis * 1.8);
    VisualAlgo::Matrix matrix(KERNEL_SIZE, KERNEL_SIZE, 0);
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
        VisualAlgo::Matrix on_center_off_surround = gaussian(KERNEL_SIZE, KERNEL_SIZE, C, ALPHA) * B - gaussian(KERNEL_SIZE, KERNEL_SIZE, E, BETA) * D;
        VisualAlgo::Matrix numerator = input.cross_correlation(on_center_off_surround, KERNEL_SIZE / 2, 1);

        VisualAlgo::Matrix denominator_kernel = gaussian(KERNEL_SIZE, KERNEL_SIZE, C, ALPHA) + gaussian(KERNEL_SIZE, KERNEL_SIZE, E, BETA);
        VisualAlgo::Matrix denominator = input.cross_correlation(denominator_kernel, KERNEL_SIZE / 2, 1) + A;

        VisualAlgo::Matrix output = numerator / denominator;
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
        VisualAlgo::Matrix off_center_on_surround = gaussian(KERNEL_SIZE, KERNEL_SIZE, E, BETA) * D - gaussian(KERNEL_SIZE, KERNEL_SIZE, C, ALPHA) * B;
        VisualAlgo::Matrix numerator = input.cross_correlation(off_center_on_surround, KERNEL_SIZE / 2, 1) + A * S;

        VisualAlgo::Matrix denominator_kernel = gaussian(KERNEL_SIZE, KERNEL_SIZE, C, ALPHA) + gaussian(KERNEL_SIZE, KERNEL_SIZE, E, BETA);
        VisualAlgo::Matrix denominator = input.cross_correlation(denominator_kernel, KERNEL_SIZE / 2, 1) + A;

        VisualAlgo::Matrix output = numerator / denominator;
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

        // L_kernel.save("results/SegmentationAndGrouping/FBF/simple_cell_L_kernel_" + std::to_string(theta) + ".ppm", true);
        // R_kernel.save("results/SegmentationAndGrouping/FBF/simple_cell_R_kernel_" + std::to_string(theta) + ".ppm", true);
        // whole_kernel.save("results/SegmentationAndGrouping/FBF/simple_cell_kernel_" + std::to_string(theta) + ".ppm", true);

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
    const int scale;
    const float EPSILON = 0.1;
    const float MU = 5;
    const float TAU = 0.1;
    const float THETA_INCREMENT = M_PI / 8;

    HypercomplexCellFirstCompetitiveStage(int scale) : scale(scale)
    {
    }

    VisualAlgo::Matrix oriented_competition_kernel(float theta)
    {
        int KERNEL_SIZE;
        if (scale == 1)
        {
            KERNEL_SIZE = 8;
        }
        else
        {
            KERNEL_SIZE = 16;
        }
        // The oriented competition kernel is positive everywhere except
        // along a one-pixel-wide line at the specified angle.
        VisualAlgo::Matrix kernel(KERNEL_SIZE, KERNEL_SIZE, 1);
        for (int i = 0; i < KERNEL_SIZE; i++)
        {
            for (int j = 0; j < KERNEL_SIZE; j++)
            {
                float x = i - KERNEL_SIZE / 2;
                float y = j - KERNEL_SIZE / 2;
                float rotated_y = x * sin(theta) + y * cos(theta);
                if (abs(rotated_y) <= 0.5)
                {
                    kernel.set(i, j, 0);
                }
            }
        }
        
        // Normalize the kernel.
        kernel /= kernel.sum();

        kernel.save("results/SegmentationAndGrouping/FBF/oriented_competition_kernel_" + std::to_string(theta) + ".ppm", true);

        return kernel;
    }

    std::vector<VisualAlgo::Matrix> apply(const std::vector<VisualAlgo::Matrix>& complex_cells)
    {
        std::vector<VisualAlgo::Matrix> output;
        for (int theta_i = 0; theta_i < complex_cells.size(); theta_i++)
        {
            VisualAlgo::Matrix G = oriented_competition_kernel(theta_i * THETA_INCREMENT);

            // D will be divived by the EPSILON + MU * (\sum_m \sum_{p, q} C(p, q, m) * C(p, q, m))
            // The sum is over all the complex cells.
            VisualAlgo::Matrix denominator = VisualAlgo::Matrix(complex_cells[theta_i].rows, complex_cells[theta_i].cols, 0);

            for (int theta_j = 0; theta_j < complex_cells.size(); theta_j++)
            {
                denominator += complex_cells[theta_i].cross_correlation(G);
            }  
            denominator = denominator * MU + EPSILON;

            // The numerator is the complex cell.
            VisualAlgo::Matrix numerator = complex_cells[theta_i];

            // Divide the numerator by the denominator.
            VisualAlgo::Matrix D = (numerator / denominator) - TAU;

            // Rectify the output.
            D.relu();

            // Save the output.
            output.push_back(D);
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

    void FBF::set_debug_dir(std::string dir)
    {
        debug_dir = dir;
    }

    Matrix FBF::apply(Matrix input)
    {        
        // Step 1: Discounting the Illuminant using the Shunting On and Shunting Off Cells
        auto shunting_on_cell = ShuntingOnCell();
        auto shunting_off_cell = ShuntingOffCell();
        Matrix shunting_on_output = shunting_on_cell.apply(input);
        Matrix shunting_off_output = shunting_off_cell.apply(input);

        // Save the shunting on and off outputs for debugging.
        if (debug_dir != "")
        {
            shunting_on_output.save(debug_dir + "/step1_shunting_on_output.ppm", true);
            shunting_off_output.save(debug_dir + "/step1_shunting_off_output.ppm", true);
        }

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

                if (debug_dir != "")
                {
                    simple_on_l.save(debug_dir + "/step2a_simple_on_l_" + std::to_string(s) + "_" + std::to_string(i) + ".ppm", true);
                    simple_on_r.save(debug_dir + "/step2a_simple_on_r_" + std::to_string(s) + "_" + std::to_string(i) + ".ppm", true);
                    simple_off_l.save(debug_dir + "/step2a_simple_off_l_" + std::to_string(s) + "_" + std::to_string(i) + ".ppm", true);
                    simple_off_r.save(debug_dir + "/step2a_simple_off_r_" + std::to_string(s) + "_" + std::to_string(i) + ".ppm", true);
                }
                
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
        if (debug_dir != "")
        {
            for (int i = 0; i < 8; i++)
            {
                complex_cells_scale_1[i].save(debug_dir + "/step2b_complex_cells_scale_1_" + std::to_string(i) + ".ppm", true);
                complex_cells_scale_2[i].save(debug_dir + "/step2b_complex_cells_scale_2_" + std::to_string(i) + ".ppm", true);
            }
        }

        // Step 2c: Hypercomplex Cells (First Competitive Stage - Noise Suppression Near Boundary)
        // Similar to non-maximum suppression - the complex cells excite the 
        // hypercomplex cells if they are collinear. Otherwise, they inhibit.
        std::vector<Matrix> hypercomplex_cells_scale_1;  // 8 orientations
        std::vector<Matrix> hypercomplex_cells_scale_2;  // 8 orientations
        hypercomplex_cells_scale_1 = HypercomplexCellFirstCompetitiveStage(1).apply(complex_cells_scale_1);
        hypercomplex_cells_scale_2 = HypercomplexCellFirstCompetitiveStage(2).apply(complex_cells_scale_2);
        if (debug_dir != "")
        {
            for (int i = 0; i < 8; i++)
            {
                hypercomplex_cells_scale_1[i].save(debug_dir + "/step2c_hypercomplex_cells_first_stage_scale_1_" + std::to_string(i) + ".ppm", true);
                hypercomplex_cells_scale_2[i].save(debug_dir + "/step2c_hypercomplex_cells_first_stage_scale_2_" + std::to_string(i) + ".ppm", true);
            }
        }

        // Step 2d: Hypercomplex Cells (Second Competitive Stage)
        // Winner-Take-All - Only the oreintation with the highest response is kept.
        Matrix hypercomplex_cells_scale_1_second_stage = Matrix(hypercomplex_cells_scale_1[0].rows, hypercomplex_cells_scale_1[0].cols, -99999);
        Matrix hypercomplex_cells_scale_2_second_stage = Matrix(hypercomplex_cells_scale_2[0].rows, hypercomplex_cells_scale_2[0].cols, -99999);

        for (int theta_i = 0; theta_i < 8; theta_i++)
        {
            hypercomplex_cells_scale_1_second_stage = Matrix::elementwise_max(hypercomplex_cells_scale_1_second_stage, hypercomplex_cells_scale_1[theta_i]);
            hypercomplex_cells_scale_2_second_stage = Matrix::elementwise_max(hypercomplex_cells_scale_2_second_stage, hypercomplex_cells_scale_2[theta_i]);
        }
        if (debug_dir != "")
        {
            hypercomplex_cells_scale_1_second_stage.save(debug_dir + "/step2d_hypercomplex_cells_second_stage_scale_1.ppm", true);
            hypercomplex_cells_scale_2_second_stage.save(debug_dir + "/step2d_hypercomplex_cells_second_stage_scale_2.ppm", true);
        }

        // Step 2e: Multiple Scale Interaction: Boundary Localization and Noise Suppression
        


        // Step 2f: Long-Range Cooporation: Boundary Completion

        // CORT-X 2 Ouput

        // Step 3: Filling-In

        // Step 4: Figure-Ground Separation
        Matrix percept(input.rows, input.cols, 0);

        return percept;
    }
}