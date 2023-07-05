#include "matrix.hpp"

#include <vector>
#include <cmath>
#include <stdexcept>

namespace VisualAlgo
{
    // Constructors
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
        Matrix::check_dim_equal(other);
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

    Matrix Matrix::matmul(const Matrix &other)
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

    // Private
    void Matrix::check_dim_equal(const Matrix &other)
    {
        if (this->rows != other.rows || this->cols != other.cols)
            throw std::invalid_argument("Matrix dimensions must be equal");
    }
}
