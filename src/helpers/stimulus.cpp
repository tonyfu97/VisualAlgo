#include "stimulus.hpp"
#include "matrix.hpp"

#include <random>
#include <stdexcept>

namespace VisualAlgo::Stimulus
{
    Matrix random_mondrian(int rows, int cols, int num_rectangles)
    {
        // Create a random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, std::max(rows, cols) - 1);

        // Create the new matrix
        Matrix output(rows, cols, 0);

        // Draw squares
        for (int n = 0; n < num_rectangles; ++n)
        {
            // Choose random positions for the corners
            int x1 = dis(gen);
            int y1 = dis(gen);
            int x2 = dis(gen);
            int y2 = dis(gen);

            // Make sure x1 <= x2 and y1 <= y2
            if (x1 > x2)
                std::swap(x1, x2);
            if (y1 > y2)
                std::swap(y1, y2);

            // Stay within matrix boundaries
            x2 = std::min(x2, rows - 1);
            y2 = std::min(y2, cols - 1);

            // Randomly choose a value in range [0, 1]
            float value = dis(gen) / (float)std::max(rows, cols);

            // Draw the square
            for (int i = x1; i <= x2; ++i)
            {
                for (int j = y1; j <= y2; ++j)
                {
                    output.set(i, j, value);
                }
            }
        }

        return output;
    }
    
    // Randomly change some percentage of pixels to the any value in [0, 1] range
    void add_noise(Matrix &matrix, float noise_probability)
    {
        if (noise_probability < 0 || noise_probability > 1)
            throw std::invalid_argument("Noise probability must be in range [0, 1]");
        // Create a random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);

        // Add noise
        for (int i = 0; i < matrix.rows; ++i)
        {
            for (int j = 0; j < matrix.cols; ++j)
            {
                if (dis(gen) < noise_probability)
                {
                    matrix.set(i, j, dis(gen));
                }
            }
        }
    }
}
