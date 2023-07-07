#include "SegmentationAndGrouping.hpp"
#include "helpers/matrix.hpp"

#include <cmath>
#include <stdexcept>

// Grossberg and Wyse (1992) take the log inside of the exponential. This is not a standard gaussian function.
static float gaussian(float p, float q, float i, float j, float C_or_E, float alpha_or_beta)
{
    return C_or_E * exp(-pow(alpha_or_beta, -2) * log(2 * (p - i) * (p - i) + 2 * (q - j) * (q - j)));
}

static void draw_half_ellipse(VisualAlgo::Matrix &matrix, int major_axis, int minor_axis, float theta, float fill_value = 1, bool is_left = true)
{
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
}

struct ShuntingOnCell
{
    float A, B, C, D, E, ALPHA, BETA;
    const int KERNEL_SIZE = 10;

    ShuntingOnCell(float A = 134, float B = 1, float C = 7, float D = 0.5, float E = 3.333, float ALPHA = 1.3, float BETA = 1.875) : A(A), B(B), C(C), D(D), E(E), ALPHA(ALPHA), BETA(BETA)
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
    float A, B, C, D, E, S, ALPHA, BETA;
    const int KERNEL_SIZE = 10;

    ShuntingOffCell(float A = 134, float B = 1, float C = 7, float D = 0.5, float E = 3.333, float S = 0.2, float ALPHA = 1.3, float BETA = 1.875) : A(A), B(B), C(C), D(D), E(E), S(S), ALPHA(ALPHA), BETA(BETA)
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
    float theta;        // in radians
    int scale;          // 1 or 2
    bool is_left;       // Why is this necessary? Can't we just use theta?
    int major_axis, minor_axis;
    float alpha;        // threshold contrast parameter
    float beta = 0.012; // threshold noise parameter
    const int KERNEL_SIZE = 20;

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
        VisualAlgo::Matrix output(input.rows, input.cols, 0);

        // Precompute the kernels. There are two halves.
        VisualAlgo::Matrix L_kernel(KERNEL_SIZE, KERNEL_SIZE, 0);
        VisualAlgo::Matrix R_kernel(KERNEL_SIZE, KERNEL_SIZE, 0);
        draw_half_ellipse(L_kernel, major_axis, minor_axis, theta, 1, true);
        draw_half_ellipse(R_kernel, major_axis, minor_axis, theta, 1, false);

        // Used for normalization later.
        float L_kernel_sum = L_kernel.sum();
        float R_kernel_sum = R_kernel.sum();

        for (int i = 0; i < input.rows; i++)
        {
            for (int j = 0; j < input.cols; j++)
            {
                float L_sum = 0;
                float R_sum = 0;
                for (int p = -KERNEL_SIZE / 2; p <= KERNEL_SIZE / 2; p++)
                {
                    for (int q = -KERNEL_SIZE / 2; q <= KERNEL_SIZE / 2; q++)
                    {
                        int x = i + p;
                        int y = j + q;

                        // If out of bounds, continue to the next iteration.
                        if (x < 0 || y < 0 || x >= input.rows || y >= input.cols)
                            continue;

                        // Apply cross-orientation
                        L_sum += input.get(x, y) * L_kernel.get(p + KERNEL_SIZE / 2, q + KERNEL_SIZE / 2);
                        R_sum += input.get(x, y) * R_kernel.get(p + KERNEL_SIZE / 2, q + KERNEL_SIZE / 2);
                    }
                }

                L_sum /= L_kernel_sum;
                R_sum /= R_kernel_sum;

                if (is_left)
                {
                    output.set(i, j, std::max(0.0f, L_sum - alpha * R_sum - beta));
                }
                else
                {
                    output.set(i, j, std::max(0.0f, R_sum - alpha * L_sum - beta));
                }
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
        Matrix percept(input.rows, input.cols, 0);

        // Step 1: Discounting the Illuminant using the Shunting On and Shunting Off Cells
        ShuntingOnCell shunting_on_cell(A, B, C, D, E, ALPHA, BETA);
        ShuntingOffCell shunting_off_cell(A, B, C, D, E, S, ALPHA, BETA);

        Matrix shunting_on_output = shunting_on_cell.apply(input);
        Matrix shunting_off_output = shunting_off_cell.apply(input);

        // Step 2: CORT-X 2 Filter

        return percept;
    }
}