#include "TestHarness.h"
#include "helpers/matrix.hpp"

#include <vector>

namespace VisualAlgo
{
    TEST(MatrixTestSuite, MatrixConstructor)
    {
        Matrix m(2, 3);
        CHECK_EQUAL(2, m.rows);
        CHECK_EQUAL(3, m.cols);
        CHECK_EQUAL(0, m.data[0][0]);
        CHECK_EQUAL(0, m.data[0][1]);
        CHECK_EQUAL(0, m.data[0][2]);
        CHECK_EQUAL(0, m.data[1][0]);
        CHECK_EQUAL(0, m.data[1][1]);
        CHECK_EQUAL(0, m.data[1][2]);

        bool exceptionThrown = false;
        try
        {
            Matrix m(-1, 3);
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }

    TEST(MatrixTestSuite, MatrixConstructorWithValue)
    {
        Matrix m(2, 3, 1);
        CHECK_EQUAL(2, m.rows);
        CHECK_EQUAL(3, m.cols);
        CHECK_EQUAL(1, m.data[0][0]);
        CHECK_EQUAL(1, m.data[0][1]);
        CHECK_EQUAL(1, m.data[0][2]);
        CHECK_EQUAL(1, m.data[1][0]);
        CHECK_EQUAL(1, m.data[1][1]);
        CHECK_EQUAL(1, m.data[1][2]);

        bool exceptionThrown = false;
        try
        {
            Matrix m(-1, 3, 1);
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }

    TEST(MatrixTestSuite, MatrixConstructorWithVector)
    {
        std::vector<std::vector<float>> data = {{1, 2, 3}, {4, 5, 6}};
        Matrix m(data);
        CHECK_EQUAL(2, m.rows);
        CHECK_EQUAL(3, m.cols);
        CHECK_EQUAL(1, m.data[0][0]);
        CHECK_EQUAL(2, m.data[0][1]);
        CHECK_EQUAL(3, m.data[0][2]);
        CHECK_EQUAL(4, m.data[1][0]);
        CHECK_EQUAL(5, m.data[1][1]);
        CHECK_EQUAL(6, m.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixCopyConstructor)
    {
        std::vector<std::vector<float>> data = {{1, 2, 3}, {4, 5, 6}};
        Matrix m1(data);
        Matrix m2(m1);
        CHECK_EQUAL(2, m2.rows);
        CHECK_EQUAL(3, m2.cols);
        CHECK_EQUAL(1, m2.data[0][0]);
        CHECK_EQUAL(2, m2.data[0][1]);
        CHECK_EQUAL(3, m2.data[0][2]);
        CHECK_EQUAL(4, m2.data[1][0]);
        CHECK_EQUAL(5, m2.data[1][1]);
        CHECK_EQUAL(6, m2.data[1][2]);

        // Check if m1 and m2 are independent
        m1.set(0, 0, 0);
        CHECK_EQUAL(0, m1.data[0][0]);
        CHECK_EQUAL(1, m2.data[0][0]);
    }

    TEST(MatrixTestSuite, MatrixAssignmentOperator)
    {
       std::vector<std::vector<float>> data = {{1, 2, 3}, {4, 5, 6}};
        Matrix m1(data);
        Matrix m2 = m1;
        CHECK_EQUAL(2, m2.rows);
        CHECK_EQUAL(3, m2.cols);
        CHECK_EQUAL(1, m2.data[0][0]);
        CHECK_EQUAL(2, m2.data[0][1]);
        CHECK_EQUAL(3, m2.data[0][2]);
        CHECK_EQUAL(4, m2.data[1][0]);
        CHECK_EQUAL(5, m2.data[1][1]);
        CHECK_EQUAL(6, m2.data[1][2]);

        // Check if m1 and m2 are independent
        m1.set(0, 0, 0);
        CHECK_EQUAL(0, m1.data[0][0]);
        CHECK_EQUAL(1, m2.data[0][0]);
    }

    TEST(MatrixTestSuite, MatrixSetAndGet)
    {
        Matrix m(2, 3);
        m.set(0, 0, 1);
        m.set(0, 1, 2);
        m.set(0, 2, 3);
        m.set(1, 0, 4);
        m.set(1, 1, 5);
        m.set(1, 2, 6);
        CHECK_EQUAL(1, m.get(0, 0));
        CHECK_EQUAL(2, m.get(0, 1));
        CHECK_EQUAL(3, m.get(0, 2));
        CHECK_EQUAL(4, m.get(1, 0));
        CHECK_EQUAL(5, m.get(1, 1));
        CHECK_EQUAL(6, m.get(1, 2));
    }

    TEST(MatrixTestSuite, MatrixOperatorPlus)
    {
        Matrix m1(2, 3, 1);
        Matrix m2(2, 3, 2);
        Matrix m3 = m1 + m2;
        CHECK_EQUAL(2, m3.rows);
        CHECK_EQUAL(3, m3.cols);
        CHECK_EQUAL(3, m3.data[0][0]);
        CHECK_EQUAL(3, m3.data[0][1]);
        CHECK_EQUAL(3, m3.data[0][2]);
        CHECK_EQUAL(3, m3.data[1][0]);
        CHECK_EQUAL(3, m3.data[1][1]);
        CHECK_EQUAL(3, m3.data[1][2]);

        bool exceptionThrown = false;
        try
        {
            Matrix m4(2, 3, 1);
            Matrix m5(3, 2, 2);
            Matrix m6 = m4 + m5;
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }

    TEST(MatrixTestSuite, MatrixOperatorMinus)
    {
        Matrix m1(2, 3, 1);
        Matrix m2(2, 3, 2);
        Matrix m3 = m1 - m2;
        CHECK_EQUAL(2, m3.rows);
        CHECK_EQUAL(3, m3.cols);
        CHECK_EQUAL(-1, m3.data[0][0]);
        CHECK_EQUAL(-1, m3.data[0][1]);
        CHECK_EQUAL(-1, m3.data[0][2]);
        CHECK_EQUAL(-1, m3.data[1][0]);
        CHECK_EQUAL(-1, m3.data[1][1]);
        CHECK_EQUAL(-1, m3.data[1][2]);

        bool exceptionThrown = false;
        try
        {
            Matrix m4(2, 3, 1);
            Matrix m5(3, 2, 2);
            Matrix m6 = m4 - m5;
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }

    TEST(MatrixTestSuite, MatrixOperatorMultiply)
    {
        Matrix m1(2, 3, 1);
        Matrix m2(2, 3, 2);
        Matrix m3 = m1 * m2;
        CHECK_EQUAL(2, m3.rows);
        CHECK_EQUAL(3, m3.cols);
        CHECK_EQUAL(2, m3.data[0][0]);
        CHECK_EQUAL(2, m3.data[0][1]);
        CHECK_EQUAL(2, m3.data[0][2]);
        CHECK_EQUAL(2, m3.data[1][0]);
        CHECK_EQUAL(2, m3.data[1][1]);
        CHECK_EQUAL(2, m3.data[1][2]);

        bool exceptionThrown = false;
        try
        {
            Matrix m4(2, 3, 1);
            Matrix m5(3, 2, 2);
            Matrix m6 = m4 * m5;
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }

    TEST(MatrixTestSuite, MatrixOperatorDivide)
    {
        Matrix m1(2, 3, 1);
        Matrix m2(2, 3, 2);
        Matrix m3 = m1 / m2;
        CHECK_EQUAL(2, m3.rows);
        CHECK_EQUAL(3, m3.cols);
        CHECK_EQUAL(0.5, m3.data[0][0]);
        CHECK_EQUAL(0.5, m3.data[0][1]);
        CHECK_EQUAL(0.5, m3.data[0][2]);
        CHECK_EQUAL(0.5, m3.data[1][0]);
        CHECK_EQUAL(0.5, m3.data[1][1]);
        CHECK_EQUAL(0.5, m3.data[1][2]);

        bool exceptionThrown = false;
        try
        {
            Matrix m4(2, 3, 1);
            Matrix m5(3, 2, 2);
            Matrix m6 = m4 / m5;
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }

    TEST(MatrixTestSuite, MatrixOperatorPlusEqual)
    {
        Matrix m1(2, 3, 1);
        Matrix m2(2, 3, 2);
        m1 += m2;
        CHECK_EQUAL(2, m1.rows);
        CHECK_EQUAL(3, m1.cols);
        CHECK_EQUAL(3, m1.data[0][0]);
        CHECK_EQUAL(3, m1.data[0][1]);
        CHECK_EQUAL(3, m1.data[0][2]);
        CHECK_EQUAL(3, m1.data[1][0]);
        CHECK_EQUAL(3, m1.data[1][1]);
        CHECK_EQUAL(3, m1.data[1][2]);

        bool exceptionThrown = false;
        try
        {
            Matrix m3(2, 3, 1);
            Matrix m4(3, 2, 2);
            m3 += m4;
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }

    TEST(MatrixTestSuite, MatrixOperatorMinusEqual)
    {
        Matrix m1(2, 3, 1);
        Matrix m2(2, 3, 2);
        m1 -= m2;
        CHECK_EQUAL(2, m1.rows);
        CHECK_EQUAL(3, m1.cols);
        CHECK_EQUAL(-1, m1.data[0][0]);
        CHECK_EQUAL(-1, m1.data[0][1]);
        CHECK_EQUAL(-1, m1.data[0][2]);
        CHECK_EQUAL(-1, m1.data[1][0]);
        CHECK_EQUAL(-1, m1.data[1][1]);
        CHECK_EQUAL(-1, m1.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixOperatorMultiplyEqual)
    {
        Matrix m1(2, 3, 1);
        Matrix m2(2, 3, 2);
        m1 *= m2;
        CHECK_EQUAL(2, m1.rows);
        CHECK_EQUAL(3, m1.cols);
        CHECK_EQUAL(2, m1.data[0][0]);
        CHECK_EQUAL(2, m1.data[0][1]);
        CHECK_EQUAL(2, m1.data[0][2]);
        CHECK_EQUAL(2, m1.data[1][0]);
        CHECK_EQUAL(2, m1.data[1][1]);
        CHECK_EQUAL(2, m1.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixOperatorDivideEqual)
    {
        Matrix m1(2, 3, 1);
        Matrix m2(2, 3, 2);
        m1 /= m2;
        CHECK_EQUAL(2, m1.rows);
        CHECK_EQUAL(3, m1.cols);
        CHECK_EQUAL(0.5, m1.data[0][0]);
        CHECK_EQUAL(0.5, m1.data[0][1]);
        CHECK_EQUAL(0.5, m1.data[0][2]);
        CHECK_EQUAL(0.5, m1.data[1][0]);
        CHECK_EQUAL(0.5, m1.data[1][1]);
        CHECK_EQUAL(0.5, m1.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixOperatorPlusScalar)
    {
        Matrix m1(2, 3, 1);
        Matrix m2 = m1 + 2;
        CHECK_EQUAL(2, m2.rows);
        CHECK_EQUAL(3, m2.cols);
        CHECK_EQUAL(3, m2.data[0][0]);
        CHECK_EQUAL(3, m2.data[0][1]);
        CHECK_EQUAL(3, m2.data[0][2]);
        CHECK_EQUAL(3, m2.data[1][0]);
        CHECK_EQUAL(3, m2.data[1][1]);
        CHECK_EQUAL(3, m2.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixOperatorMinusScalar)
    {
        Matrix m1(2, 3, 1);
        Matrix m2 = m1 - 2;
        CHECK_EQUAL(2, m2.rows);
        CHECK_EQUAL(3, m2.cols);
        CHECK_EQUAL(-1, m2.data[0][0]);
        CHECK_EQUAL(-1, m2.data[0][1]);
        CHECK_EQUAL(-1, m2.data[0][2]);
        CHECK_EQUAL(-1, m2.data[1][0]);
        CHECK_EQUAL(-1, m2.data[1][1]);
        CHECK_EQUAL(-1, m2.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixOperatorMultiplyScalar)
    {
        Matrix m1(2, 3, 1);
        Matrix m2 = m1 * 2;
        CHECK_EQUAL(2, m2.rows);
        CHECK_EQUAL(3, m2.cols);
        CHECK_EQUAL(2, m2.data[0][0]);
        CHECK_EQUAL(2, m2.data[0][1]);
        CHECK_EQUAL(2, m2.data[0][2]);
        CHECK_EQUAL(2, m2.data[1][0]);
        CHECK_EQUAL(2, m2.data[1][1]);
        CHECK_EQUAL(2, m2.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixOperatorDivideScalar)
    {
        Matrix m1(2, 3, 1);
        Matrix m2 = m1 / 2;
        CHECK_EQUAL(2, m2.rows);
        CHECK_EQUAL(3, m2.cols);
        CHECK_EQUAL(0.5, m2.data[0][0]);
        CHECK_EQUAL(0.5, m2.data[0][1]);
        CHECK_EQUAL(0.5, m2.data[0][2]);
        CHECK_EQUAL(0.5, m2.data[1][0]);
        CHECK_EQUAL(0.5, m2.data[1][1]);
        CHECK_EQUAL(0.5, m2.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixOperatorUnaryMinus)
    {
        Matrix m1(2, 3, 1);
        Matrix m2 = -m1;
        CHECK_EQUAL(2, m2.rows);
        CHECK_EQUAL(3, m2.cols);
        CHECK_EQUAL(-1, m2.data[0][0]);
        CHECK_EQUAL(-1, m2.data[0][1]);
        CHECK_EQUAL(-1, m2.data[0][2]);
        CHECK_EQUAL(-1, m2.data[1][0]);
        CHECK_EQUAL(-1, m2.data[1][1]);
        CHECK_EQUAL(-1, m2.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixOperatorPower)
    {
        Matrix m1(2, 3, 2);
        Matrix m2 = m1 ^ 2;
        CHECK_EQUAL(2, m2.rows);
        CHECK_EQUAL(3, m2.cols);
        CHECK_EQUAL(4, m2.data[0][0]);
        CHECK_EQUAL(4, m2.data[0][1]);
        CHECK_EQUAL(4, m2.data[0][2]);
        CHECK_EQUAL(4, m2.data[1][0]);
        CHECK_EQUAL(4, m2.data[1][1]);
        CHECK_EQUAL(4, m2.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixOperatorSubscript)
    {
        Matrix m(2, 3, 1);
        m[0][0] = 2;
        m[0][1] = 3;
        m[0][2] = 4;
        m[1][0] = 5;
        m[1][1] = 6;
        m[1][2] = 7;
        CHECK_EQUAL(2, m.data[0][0]);
        CHECK_EQUAL(3, m.data[0][1]);
        CHECK_EQUAL(4, m.data[0][2]);
        CHECK_EQUAL(5, m.data[1][0]);
        CHECK_EQUAL(6, m.data[1][1]);
        CHECK_EQUAL(7, m.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixTranspose)
    {
        Matrix m(2, 3, 1);
        Matrix mT = m.transpose();
        CHECK_EQUAL(3, mT.rows);
        CHECK_EQUAL(2, mT.cols);
        CHECK_EQUAL(1, mT.data[0][0]);
        CHECK_EQUAL(1, mT.data[0][1]);
        CHECK_EQUAL(1, mT.data[1][0]);
        CHECK_EQUAL(1, mT.data[1][1]);
        CHECK_EQUAL(1, mT.data[2][0]);
        CHECK_EQUAL(1, mT.data[2][1]);
    }

    TEST(MatrixTestSuite, MatrixDot)
    {
        Matrix m1(2, 3, 1);
        Matrix m2(2, 3, 2);
        float dot = m1.dot(m2);
        CHECK_EQUAL(12, dot);
    }

    TEST(MatrixTestSuite, MatrixMatmul)
    {
        auto m1 = Matrix({{1, 2, 3}, {4, 5, 6}});
        auto m2 = Matrix({{10, 11}, {20, 21}, {30, 31}});
        auto m3 = m1.matmul(m2);
        CHECK_EQUAL(2, m3.rows);
        CHECK_EQUAL(2, m3.cols);
        CHECK_EQUAL(140, m3.data[0][0]);
        CHECK_EQUAL(146, m3.data[0][1]);
        CHECK_EQUAL(320, m3.data[1][0]);
        CHECK_EQUAL(335, m3.data[1][1]);

        bool exceptionThrown = false;
        try
        {
            auto m4 = Matrix({{1, 2, 3}, {4, 5, 6}});
            auto m5 = Matrix({{10, 11}, {20, 21}});
            auto m6 = m4.matmul(m5);
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }

    TEST(MatrixTestSuite, MatrixSum)
    {
        Matrix m(2, 3, 1);
        CHECK_EQUAL(6, m.sum());

        m[0][0] = 2;
        m[0][1] = 3;
        m[0][2] = 4;
        m[1][0] = 5;
        m[1][1] = 6;
        m[1][2] = 7;
        CHECK_EQUAL(27, m.sum());
    }

    TEST(MatrixTestSuite, MatrixMean)
    {
        Matrix m(2, 3, 1);
        CHECK_EQUAL(1, m.mean());

        m[0][0] = 2;
        m[0][1] = 3;
        m[0][2] = 4;
        m[1][0] = 5;
        m[1][1] = 6;
        m[1][2] = 7;
        CHECK_DOUBLES_EQUAL(4.5, m.mean(), 0.0001);
    }

    TEST(MatrixTestSuite, MatrixStd)
    {
        Matrix m(2, 3, 1);
        CHECK_EQUAL(0, m.std());

        m[0][0] = 2;
        m[0][1] = 3;
        m[0][2] = 4;
        m[1][0] = 5;
        m[1][1] = 6;
        m[1][2] = 7;
        CHECK_DOUBLES_EQUAL(1.70782512765, m.std(), 0.0001);
    }

    TEST(MatrixTestSuite, MatrixMax)
    {
        Matrix m(2, 3, 1);
        CHECK_EQUAL(1, m.max());

        m[0][0] = 2;
        m[0][1] = 3;
        m[0][2] = 4;
        m[1][0] = 5;
        m[1][1] = 6;
        m[1][2] = 7;
        CHECK_EQUAL(7, m.max());
    }

    TEST(MatrixTestSuite, MatrixMin)
    {
        Matrix m(2, 3, 1);
        CHECK_EQUAL(1, m.min());

        m[0][0] = 2;
        m[0][1] = 3;
        m[0][2] = 4;
        m[1][0] = 5;
        m[1][1] = 6;
        m[1][2] = 7;
        CHECK_EQUAL(2, m.min());
    }

    TEST(MatrixTestSuite, MatrixSaveLoad)
    {
        Matrix m1(2, 3, 1);
        m1.save("results/helpers/matrix/test.ppm");
        Matrix m2;
        m2.load("results/helpers/matrix/test.ppm");
        CHECK_EQUAL(2, m2.rows);
        CHECK_EQUAL(3, m2.cols);
        CHECK_EQUAL(1, m2.data[0][0]);
        CHECK_EQUAL(1, m2.data[0][1]);
        CHECK_EQUAL(1, m2.data[0][2]);
        CHECK_EQUAL(1, m2.data[1][0]);
        CHECK_EQUAL(1, m2.data[1][1]);
        CHECK_EQUAL(1, m2.data[1][2]);

        bool exceptionThrown = false;
        try
        {
            Matrix m3;
            m3.load("non_existance_file.txt");
        }
        catch (const std::runtime_error &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }

    TEST(MatrixTestSuite, MatrixSaveLoadNormalized)
    {
        Matrix m1({{0, 0, 0}, {0, 1, 2}});
        m1.save("results/helpers/matrix/test.ppm", true);
        Matrix m2;
        m2.load("results/helpers/matrix/test.ppm");
        CHECK_EQUAL(2, m2.rows);
        CHECK_EQUAL(3, m2.cols);
        CHECK_EQUAL(0, m2.data[0][0]);
        CHECK_EQUAL(0, m2.data[0][1]);
        CHECK_EQUAL(0, m2.data[0][2]);
        CHECK_EQUAL(0, m2.data[1][0]);
        CHECK_EQUAL(127, m2.data[1][1]);
        CHECK_EQUAL(255, m2.data[1][2]);

        bool exceptionThrown = false;
        try
        {
            m2 += 1; // out of [0, 255] range. Should throw exception
            m2.save("results/helpers/matrix/test.ppm", false);
        }
        catch (const std::runtime_error &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);

        exceptionThrown = false;
        try
        {
            Matrix m3(2, 3, -0.1); // out of [0, 255] range. Should throw exception
            m3.save("non_existance_file.txt", false);
        }
        catch (const std::runtime_error &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }

    TEST(MatrixTestSuite, MatrixNormalize255)
    {
        Matrix m1({{0, 0, 0}, {0, 1, 2}});
        m1.normalize255();
        CHECK_EQUAL(2, m1.rows);
        CHECK_EQUAL(3, m1.cols);
        CHECK_EQUAL(255, m1.max());
        CHECK_EQUAL(0, m1.min());
    }

    TEST(MatrixTestSuite, MatrixRelu)
    {
        Matrix m1({{0, -33, 0}, {0, 55, -2}});
        m1.relu();
        CHECK_EQUAL(2, m1.rows);
        CHECK_EQUAL(3, m1.cols);
        CHECK_EQUAL(0, m1.data[0][0]);
        CHECK_EQUAL(0, m1.data[0][1]);
        CHECK_EQUAL(0, m1.data[0][2]);
        CHECK_EQUAL(0, m1.data[1][0]);
        CHECK_EQUAL(55, m1.data[1][1]);
        CHECK_EQUAL(0, m1.data[1][2]);
    }

    TEST(MatrixTestSuite, MatrixCrossCorrelation)
    {
        // Test for Matrix Matrix::cross_correlation(const VisualAlgo::Matrix &kernel, int padding, int stride) const

        // Test 1
        Matrix m1({{1, 2, 3}, {4, 5, 6}});
        Matrix m2({{1, 2}, {3, 4}});
        Matrix m3 = m1.cross_correlation(m2, 0, 1);
        CHECK_EQUAL(1, m3.rows);
        CHECK_EQUAL(2, m3.cols);
        CHECK_EQUAL(37, m3.data[0][0]);
        CHECK_EQUAL(47, m3.data[0][1]);
        
        // Test 2
        Matrix m4({{1, 2, 3}, {4, 5, 6}});
        Matrix m5({{1, 2}, {3, 4}});
        Matrix m6 = m4.cross_correlation(m5, 1, 1);
        CHECK_EQUAL(3, m6.rows);
        CHECK_EQUAL(4, m6.cols);
        CHECK_EQUAL(4, m6.data[0][0]);
        CHECK_EQUAL(11, m6.data[0][1]);
        CHECK_EQUAL(18, m6.data[0][2]);
        CHECK_EQUAL(9, m6.data[0][3]);
        CHECK_EQUAL(18, m6.data[1][0]);
        CHECK_EQUAL(37, m6.data[1][1]);
        CHECK_EQUAL(47, m6.data[1][2]);
        CHECK_EQUAL(21, m6.data[1][3]);
        CHECK_EQUAL(8, m6.data[2][0]);
        CHECK_EQUAL(14, m6.data[2][1]);
        CHECK_EQUAL(17, m6.data[2][2]);
        CHECK_EQUAL(6, m6.data[2][3]);

        // Test 3
        Matrix m7({{1, 2, 3}, {4, 5, 6}});
        Matrix m8({{1, 2}, {3, 4}});
        Matrix m9 = m7.cross_correlation(m8, 1, 2);
        CHECK_EQUAL(2, m9.rows);
        CHECK_EQUAL(2, m9.cols);
        CHECK_EQUAL(4, m9.data[0][0]);
        CHECK_EQUAL(18, m9.data[0][1]);
        CHECK_EQUAL(8, m9.data[1][0]);
        CHECK_EQUAL(17, m9.data[1][1]);

        // Test exceptions: kernel size > matrix size
        bool exceptionThrown = false;
        try
        {
            Matrix m10({{1, 2, 3}, {4, 5, 6}});
            Matrix m11({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
            Matrix m12 = m10.cross_correlation(m11, 0, 1);
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);

        // Test exceptions: negative stride
        exceptionThrown = false;
        try
        {
            Matrix m13({{1, 2, 3}, {4, 5, 6}});
            Matrix m14({{1, 2}, {3, 4}});
            Matrix m15 = m13.cross_correlation(m14, 0, -1);
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);

        // Test exceptions: negative padding
        exceptionThrown = false;
        try
        {
            Matrix m13({{1, 2, 3}, {4, 5, 6}});
            Matrix m14({{1, 2}, {3, 4}});
            Matrix m15 = m13.cross_correlation(m14, -2, 0);
        }
        catch (const std::invalid_argument &e)
        {
            exceptionThrown = true;
        }
        CHECK_EQUAL(true, exceptionThrown);
    }
}


