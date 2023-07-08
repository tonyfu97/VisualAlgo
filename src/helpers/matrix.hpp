#pragma once

#include <vector>
#include <string>

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

        // Matrix operations
        Matrix transpose();
        float dot(const Matrix &other);
        Matrix matmul(const Matrix &other);

        // Accessors
        void set(int row, int col, float value);
        const float get(int row, int col) const;
        std::vector<float> &operator[](int row);

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
        void normalize255();
        void relu();
        Matrix cross_correlation(const VisualAlgo::Matrix &kernel, int padding, int stride) const;
        Matrix cross_correlation(const VisualAlgo::Matrix &kernel) const;  // keep the same size

        // Functions
        static Matrix zeros(int rows, int cols);
        static Matrix ones(int rows, int cols);
        static Matrix eye(int rows, int cols);
        static Matrix random(int rows, int cols);
        static Matrix random(int rows, int cols, float min, float max);
        static Matrix elementwise_max(const Matrix &a, const Matrix &b);
        static Matrix elementwise_min(const Matrix &a, const Matrix &b);

    private:
        void check_dim_equal(const Matrix &other);
        static void check_dim_equal(const Matrix &a, const Matrix &b);
    };

}
