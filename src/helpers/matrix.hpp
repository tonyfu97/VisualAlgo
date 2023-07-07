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
        void save(const std::string& filename);
        void normalize255();

    private:
        void check_dim_equal(const Matrix &other);
    };

}
