#include "Matrix.hpp"

#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>

namespace VisualAlgo
{
    // Constructors
    Matrix::Matrix()
    {
        this->rows = 0;
        this->cols = 0;
    }

    Matrix::Matrix(int rows, int cols)
    {
        if (rows <= 0 || cols <= 0)
            throw std::invalid_argument("Matrix dimensions must be positive");
        this->rows = rows;
        this->cols = cols;
        this->data = std::vector<std::vector<float>>(rows, std::vector<float>(cols, 0));
    }

    Matrix::Matrix(int rows, int cols, float value)
    {
        if (rows <= 0 || cols <= 0)
            throw std::invalid_argument("Matrix dimensions must be positive");
        this->rows = rows;
        this->cols = cols;
        this->data = std::vector<std::vector<float>>(rows, std::vector<float>(cols, value));
    }

    Matrix::Matrix(std::vector<std::vector<float>> data)
    {
        this->rows = data.size();
        this->cols = data.at(0).size();
        this->data = data;
    }

    Matrix::Matrix(const Matrix &other)
    {
        this->rows = other.rows;
        this->cols = other.cols;
        this->data = other.data;
    }

    // Element-wise operations
    Matrix &Matrix::operator=(const Matrix &other)
    {
        if (this == &other)
            return *this;
        this->rows = other.rows;
        this->cols = other.cols;
        this->data = other.data;
        return *this;
    }

    Matrix Matrix::operator+(const Matrix &other)
    {
        Matrix::check_dim_equal(other);
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) + other.get(i, j));
        return result;
    }

    Matrix Matrix::operator-(const Matrix &other)
    {
        Matrix::check_dim_equal(other);
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) - other.get(i, j));
        return result;
    }

    Matrix Matrix::operator*(const Matrix &other)
    {
        Matrix::check_dim_equal(other);
        Matrix result(this->rows, other.cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) * other.get(i, j));
        return result;
    }

    Matrix Matrix::operator/(const Matrix &other)
    {
        Matrix::check_dim_equal(other);
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < other.cols; j++)
                result.set(i, j, this->get(i, j) / other.get(i, j));
        return result;
    }

    Matrix Matrix::operator+(const float &other)
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) + other);
        return result;
    }

    Matrix Matrix::operator-(const float &other)
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) - other);
        return result;
    }

    Matrix Matrix::operator*(const float &other)
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) * other);
        return result;
    }

    Matrix Matrix::operator/(const float &other)
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) / other);
        return result;
    }

    Matrix Matrix::operator-()
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, -this->get(i, j));
        return result;
    }

    Matrix Matrix::operator^(const int &other)
    {
        Matrix result(this->rows, this->cols, 1);
        for (int i = 0; i < other; i++)
            result *= *this;
        return result;
    }

    Matrix &Matrix::operator+=(const Matrix &other)
    {
        Matrix::check_dim_equal(other);
        *this = *this + other;
        return *this;
    }

    Matrix &Matrix::operator-=(const Matrix &other)
    {
        Matrix::check_dim_equal(other);
        *this = *this - other;
        return *this;
    }

    Matrix &Matrix::operator*=(const Matrix &other)
    {
        Matrix::check_dim_equal(other);
        *this = *this * other;
        return *this;
    }

    Matrix &Matrix::operator/=(const Matrix &other)
    {
        Matrix::check_dim_equal(other);
        *this = *this / other;
        return *this;
    }

    Matrix &Matrix::operator+=(const float &other)
    {
        *this = *this + other;
        return *this;
    }

    Matrix &Matrix::operator-=(const float &other)
    {
        *this = *this - other;
        return *this;
    }

    Matrix &Matrix::operator*=(const float &other)
    {
        *this = *this * other;
        return *this;
    }

    Matrix &Matrix::operator/=(const float &other)
    {
        *this = *this / other;
        return *this;
    }

    // Comparison
    bool Matrix::operator==(const Matrix &other) const
    {
        if (this->rows != other.rows || this->cols != other.cols)
            return false;
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                if (this->get(i, j) != other.get(i, j))
                    return false;
        return true;
    }

    bool Matrix::operator!=(const Matrix &other) const
    {
        return !(*this == other);
    }

    bool Matrix::is_close(const Matrix &other, float tolerance) const
    {
        if (this->rows != other.rows || this->cols != other.cols)
            return false;
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
            {
                float diff = this->get(i, j) - other.get(i, j);
                if (diff < -tolerance || diff > tolerance)
                    return false;
            }
        return true;
    }

    Matrix Matrix::operator>(const Matrix &other) const
    {
        Matrix::check_dim_equal(other);
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < other.cols; j++)
                result.set(i, j, this->get(i, j) > other.get(i, j));
        return result;
    }

    Matrix Matrix::operator<(const Matrix &other) const
    {
        Matrix::check_dim_equal(other);
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < other.cols; j++)
                result.set(i, j, this->get(i, j) < other.get(i, j));
        return result;
    }

    Matrix Matrix::operator>=(const Matrix &other) const
    {
        Matrix::check_dim_equal(other);
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < other.cols; j++)
                result.set(i, j, this->get(i, j) >= other.get(i, j));
        return result;
    }

    Matrix Matrix::operator<=(const Matrix &other) const
    {
        Matrix::check_dim_equal(other);
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < other.cols; j++)
                result.set(i, j, this->get(i, j) <= other.get(i, j));
        return result;
    }

    Matrix Matrix::operator>(const float &other) const
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) > other);
        return result;
    }

    Matrix Matrix::operator<(const float &other) const
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) < other);
        return result;
    }

    Matrix Matrix::operator>=(const float &other) const
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) >= other);
        return result;
    }

    Matrix Matrix::operator<=(const float &other) const
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result.set(i, j, this->get(i, j) <= other);
        return result;
    }

    // Matrix operations
    Matrix Matrix::transpose()
    {
        Matrix result(this->cols, this->rows);
        for (int i = 0; i < this->cols; i++)
            for (int j = 0; j < this->rows; j++)
                result.set(i, j, this->get(j, i));
        return result;
    }

    float Matrix::dot(const Matrix &other)
    {
        Matrix::check_dim_equal(other);
        float result = 0;
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                result += this->get(i, j) * other.get(i, j);
        return result;
    }

    Matrix Matrix::matmul(const Matrix &other) const
    {
        if (this->cols != other.rows)
            throw std::invalid_argument("Matrix dimensions must be compatible");
        Matrix result(this->rows, other.cols);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < other.cols; j++)
                for (int k = 0; k < this->cols; k++)
                    result.set(i, j, result.get(i, j) + this->get(i, k) * other.get(k, j));
        return result;
    }

    // Accessors
    void Matrix::set(int row, int col, float value)
    {
        this->data.at(row).at(col) = value;
    }

    const float Matrix::get(int row, int col) const
    {
        return this->data.at(row).at(col);
    }

    std::vector<float> &Matrix::operator[](int row)
    {
        return this->data.at(row);
    }

    std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
    {
        os << "[";
        for (int i = 0; i < matrix.rows; i++)
        {
            os << "[";
            for (int j = 0; j < matrix.cols; j++)
            {
                os << matrix.get(i, j);
                if (j != matrix.cols - 1)
                    os << ", ";
            }
            os << "]";
            if (i != matrix.rows - 1)
                os << ",\n";
        }
        os << "]";
        return os;
    }

    // Statistics
    float Matrix::sum()
    {
        float sum = 0;
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                sum += this->get(i, j);
        return sum;
    }

    float Matrix::mean()
    {
        return this->sum() / (this->rows * this->cols);
    }

    float Matrix::std()
    {
        float mean = this->mean();
        float std = 0;
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
            {
                float diff = this->get(i, j) - mean;
                std += diff * diff;
            }
        return sqrt(std / (this->rows * this->cols));
    }

    float Matrix::max()
    {
        float max = this->get(0, 0);
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
            {
                if (this->data[i][j] > max)
                    max = this->get(i, j);
            }
        return max;
    }

    float Matrix::min()
    {
        float min = this->data[0][0];
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
            {
                if (this->data[i][j] < min)
                    min = this->get(i, j);
            }
        return min;
    }

    // Image operations
    void Matrix::load(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Cannot open file: " + filename + ".");
        }

        std::string header;
        file >> header;
        if (header != "P6")
        {
            throw std::runtime_error("Can only handle PPM format (P6). Got: " + header + " instead.");
        }

        file >> this->cols >> this->rows;

        int max_value;
        file >> max_value;

        file.get(); // consume newline

        this->data = std::vector<std::vector<float>>(rows, std::vector<float>(cols, 0));

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                unsigned char r, g, b;
                file.read(reinterpret_cast<char *>(&r), 1);
                file.read(reinterpret_cast<char *>(&g), 1);
                file.read(reinterpret_cast<char *>(&b), 1);
                // convert RGB to grayscale using the ITU-R BT.709 luma transform
                this->set(i, j, 0.2126 * r + 0.7152 * g + 0.0722 * b);
            }
        }
    }

    Matrix Matrix::load(const std::string &filename, int rows, int cols)
    {
        Matrix result(rows, cols);
        result.load(filename);
        return result;
    }

    void Matrix::save(const std::string &filename, bool normalize) const
    {
        // Make a copy of the matrix. Otherwise, the normalization will affect the original matrix.
        Matrix copy = *this;

        if (normalize)
        {
            copy.normalize255();
        }
        else if (copy.max() > 255 || copy.min() < 0)
        {
            throw std::runtime_error("Image values must be between 0 and 255. Please consider normalizing.");
        }

        std::ofstream file(filename, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Cannot open file: " + filename + ".");
        }

        file << "P6\n";
        file << copy.cols << " " << copy.rows << "\n";
        file << 255 << "\n";

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                unsigned char pixel = static_cast<unsigned char>(copy.get(i, j));
                file.write(reinterpret_cast<char *>(&pixel), 1); // R
                file.write(reinterpret_cast<char *>(&pixel), 1); // G
                file.write(reinterpret_cast<char *>(&pixel), 1); // B
            }
        }
    }

    void Matrix::normalize()
    {
        float min_value = this->get(0, 0);
        float max_value = this->get(0, 0);

        for (const auto &row : this->data)
        {
            for (const auto &value : row)
            {
                min_value = std::min(min_value, value);
                max_value = std::max(max_value, value);
            }
        }

        float range = max_value - min_value;
        if (range == 0)
            return;
        for (auto &row : this->data)
        {
            for (auto &value : row)
            {
                value = (value - min_value) / range;
            }
        }
    }

    void Matrix::normalize255()
    {
        float min_value = this->get(0, 0);
        float max_value = this->get(0, 0);

        for (const auto &row : this->data)
        {
            for (const auto &value : row)
            {
                min_value = std::min(min_value, value);
                max_value = std::max(max_value, value);
            }
        }

        float range = max_value - min_value;
        if (range == 0)
            return;
        for (auto &row : this->data)
        {
            for (auto &value : row)
            {
                value = ((value - min_value) / range) * 255;
            }
        }
    }

    void Matrix::relu()
    {
        for (auto &row : this->data)
        {
            for (auto &value : row)
            {
                value = std::max(value, 0.0f);
            }
        }
    }

    void Matrix::abs()
    {
        for (auto &row : this->data)
        {
            for (auto &value : row)
            {
                value = std::abs(value);
            }
        }
    }

    Matrix Matrix::cross_correlate(const VisualAlgo::Matrix &kernel, int padding, int stride) const // TODO: Vectorize
    {
        if (kernel.rows > rows || kernel.cols > cols)
        {
            throw std::invalid_argument("Kernel dimensions cannot be larger than the input matrix dimensions.");
        }

        if (stride <= 0)
        {
            throw std::invalid_argument("Stride must be a positive integer.");
        }

        if (padding < 0)
        {
            throw std::invalid_argument("Padding cannot be negative.");
        }
        int out_rows = (rows + 2 * padding - kernel.rows) / stride + 1;
        int out_cols = (cols + 2 * padding - kernel.cols) / stride + 1;

        VisualAlgo::Matrix output(out_rows, out_cols, 0);

        for (int i = 0; i < out_rows; ++i)
        {
            for (int j = 0; j < out_cols; ++j)
            {
                float sum = 0;
                for (int p = 0; p < kernel.rows; ++p)
                {
                    for (int q = 0; q < kernel.cols; ++q)
                    {
                        int x = stride * i + p - padding;
                        int y = stride * j + q - padding;

                        // If within bounds of original image
                        if (x >= 0 && y >= 0 && x < rows && y < cols)
                        {
                            sum += get(x, y) * kernel.get(p, q);
                        }
                    }
                }
                output.set(i, j, sum);
            }
        }

        return output;
    }

    Matrix Matrix::cross_correlate(const VisualAlgo::Matrix &kernel) const
    {
        VisualAlgo::Matrix output(rows, cols);

        int kernel_center_x = kernel.rows / 2;
        int kernel_center_y = kernel.cols / 2;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; j++)
            {
                float sum = 0;
                for (int p = 0; p < kernel.rows; ++p)
                {
                    for (int q = 0; q < kernel.cols; ++q)
                    {
                        // Compute coordinates in input image, including possible overhang
                        int x = i + p - kernel_center_x;
                        int y = j + q - kernel_center_y;

                        // Handle overhang with mirror padding
                        if (x < 0)
                        {
                            x = -x;
                        }
                        if (x >= rows)
                        {
                            x = 2 * rows - x - 1;
                        }
                        if (y < 0)
                        {
                            y = -y;
                        }
                        if (y >= cols)
                        {
                            y = 2 * cols - y - 1;
                        }

                        sum += get(x, y) * kernel.get(p, q);
                    }
                }
                output.set(i, j, sum);
            }
        }
        return output;
    }

    Matrix Matrix::flip() const
    {
        Matrix flipped(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                flipped.set(i, j, get(rows - i - 1, cols - j - 1));
            }
        }
        return flipped;
    }

    Matrix Matrix::convolve(const VisualAlgo::Matrix &kernel, int padding, int stride) const
    {
        Matrix flipped_kernel = kernel.flip();
        return this->cross_correlate(flipped_kernel, padding, stride);
    }

    Matrix Matrix::convolve(const VisualAlgo::Matrix &kernel) const
    {
        Matrix flipped_kernel = kernel.flip();
        return this->cross_correlate(flipped_kernel);
    }

    // Functions
    Matrix Matrix::zeros(int rows, int cols)
    {
        return Matrix(rows, cols, 0);
    }

    Matrix Matrix::ones(int rows, int cols)
    {
        return Matrix(rows, cols, 1);
    }

    Matrix Matrix::eye(int rows, int cols)
    {
        Matrix result(rows, cols, 0);
        for (int i = 0; i < std::min(rows, cols); i++)
            result.set(i, i, 1);
        return result;
    }

    Matrix Matrix::random(int rows, int cols)
    {
        return Matrix::random(rows, cols, 0, 1);
    }

    Matrix Matrix::random(int rows, int cols, float min, float max)
    {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.set(i, j, min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min))));
        return result;
    }

    Matrix Matrix::elementwise_max(const Matrix &a, const Matrix &b)
    {
        Matrix::check_dim_equal(a, b);
        Matrix result(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++)
            for (int j = 0; j < a.cols; j++)
                result.set(i, j, std::max(a.get(i, j), b.get(i, j)));
        return result;
    }

    Matrix Matrix::elementwise_min(const Matrix &a, const Matrix &b)
    {
        Matrix::check_dim_equal(a, b);
        Matrix result(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++)
            for (int j = 0; j < a.cols; j++)
                result.set(i, j, std::min(a.get(i, j), b.get(i, j)));
        return result;
    }

    // Private
    void Matrix::check_dim_equal(const Matrix &other) const
    {
        if (this->rows != other.rows || this->cols != other.cols)
            throw std::invalid_argument("Matrix dimensions must be equal. Got " + std::to_string(this->rows) + "x" + std::to_string(this->cols) + " and " + std::to_string(other.rows) + "x" + std::to_string(other.cols) + " instead.");
    }

    void Matrix::check_dim_equal(const Matrix &a, const Matrix &b)
    {
        if (a.rows != b.rows || a.cols != b.cols)
            throw std::invalid_argument("Matrix dimensions must be equal. Got " + std::to_string(a.rows) + "x" + std::to_string(a.cols) + " and " + std::to_string(b.rows) + "x" + std::to_string(b.cols) + " instead.");
    }
}
