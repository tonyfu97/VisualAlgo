#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace VisualAlgo
{
    struct Matrix
    {
        // Attributes
        int rows, cols;
        std::vector<std::vector<float>> data;

        // Constructors
        Matrix();
        Matrix(int rows, int cols);
        Matrix(int rows, int cols, float value);
        Matrix(std::vector<std::vector<float>> data);
        Matrix(const Matrix &other);

        // Element-wise operations
        Matrix &operator=(const Matrix &other);
        Matrix operator+(const Matrix &other);
        Matrix operator-(const Matrix &other);
        Matrix operator*(const Matrix &other);
        Matrix operator/(const Matrix &other);

        Matrix operator+(const float &other);
        Matrix operator-(const float &other);
        Matrix operator*(const float &other);
        Matrix operator/(const float &other);
        Matrix operator-();
        Matrix operator^(const int &other);

        Matrix &operator+=(const Matrix &other);
        Matrix &operator-=(const Matrix &other);
        Matrix &operator*=(const Matrix &other);
        Matrix &operator/=(const Matrix &other);

        Matrix &operator+=(const float &other);
        Matrix &operator-=(const float &other);
        Matrix &operator*=(const float &other);
        Matrix &operator/=(const float &other);

        // Comparison
        bool operator==(const Matrix &other) const;
        bool operator!=(const Matrix &other) const;
        bool is_close(const Matrix &other, float tolerance=1e-5) const;

        // for the rest of the comparison operators, true is 1 and false is 0
        Matrix operator>(const Matrix &other) const;
        Matrix operator<(const Matrix &other) const;
        Matrix operator>=(const Matrix &other) const;
        Matrix operator<=(const Matrix &other) const;

        Matrix operator>(const float &other) const;
        Matrix operator<(const float &other) const;
        Matrix operator>=(const float &other) const;
        Matrix operator<=(const float &other) const;

        // Matrix operations
        Matrix transpose() const;
        Matrix submatrix(int row_start, int row_end, int col_start, int col_end) const;
        float det() const;
        Matrix cofactor() const;
        Matrix inverse() const;
        float dot(const Matrix &other) const;
        Matrix matmul(const Matrix &other) const;

        // Accessors
        void set(int row, int col, float value);
        const float get(int row, int col) const;
        std::vector<float> &operator[](int row);
        friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

        // Statistics
        float sum();
        float mean();
        float std();
        float max();
        float min();

        // Image operations
        void load(const std::string& filename);
        static Matrix load(const std::string& filename, int rows, int cols);
        void save(const std::string &filename, bool normalize=true) const;
        void normalize();  // [0, 1.0]
        void normalize255(); // [0, 255.0]
        void relu();
        void abs();
        Matrix cross_correlate(const VisualAlgo::Matrix &kernel, int padding, int stride) const;
        Matrix cross_correlate(const VisualAlgo::Matrix &kernel) const;  // keeps the same size, does wrap around
        Matrix flip() const;
        Matrix convolve(const VisualAlgo::Matrix &kernel, int padding, int stride) const;
        Matrix convolve(const VisualAlgo::Matrix &kernel) const;  // keeps the same size, does wrap around

        // Functions
        static Matrix zeros(int rows, int cols);
        static Matrix ones(int rows, int cols);
        static Matrix eye(int rows, int cols);
        static Matrix random(int rows, int cols);
        static Matrix random(int rows, int cols, float min, float max);
        static Matrix elementwise_max(const Matrix &a, const Matrix &b);
        static Matrix elementwise_min(const Matrix &a, const Matrix &b);

    private:
        void check_dim_equal(const Matrix &other) const;
        static void check_dim_equal(const Matrix &a, const Matrix &b);
    };

}
