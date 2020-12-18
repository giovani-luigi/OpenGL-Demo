#pragma once

#include <algorithm>
#include <iomanip>

#include "Vector4.h"

using namespace std;

class Matrix4x4
{
public:

    // static
    const static Matrix4x4& empty();
    const static Matrix4x4& identity();

    // instance

    // constructors
    Matrix4x4();
    Matrix4x4(const Matrix4x4& from);
    explicit Matrix4x4(float v[]); // non converting constructor

    // methods
    void transpose();
    void make_identity();

    // getters
    Matrix4x4 get_transpose() const;
    const float* get_array() const { return m_Array; }

    // operators
    float get(const int i) const { return m_Array[i]; }
    float get(const int row, const int col) const { return m_Array[row * 4 + col]; }
    void set(const int row, const int col, float value) { m_Array[row * 4 + col] = value; }
    float& operator[](int i) { return m_Array[i]; }
    const float& operator[](int i) const { return m_Array[i]; }
    Matrix4x4 operator*(const Matrix4x4& other) const;
    Matrix4x4 operator+(const Matrix4x4& other) const;
    Matrix4x4 operator-(const Matrix4x4& other) const;
    Vector4 operator*(const Vector4& v) const;
    Matrix4x4& operator*(const float scale);
    Matrix4x4& operator/(const float scale);

protected:

    float m_Array[4 * 4];
};


inline std::ostream& operator<<(std::ostream& out, const Matrix4x4& m)
{
    return
        out << std::fixed << std::setprecision(6) << std::setfill(' ')
        << "[" << setw(6) << m[0] << "][" << setw(6) << m[1] << "][" << setw(6) << m[2] << "][" << setw(6) << m[3] <<
        "]" << std::endl
        << "[" << setw(6) << m[4] << "][" << setw(6) << m[5] << "][" << setw(6) << m[6] << "][" << setw(6) << m[7] <<
        "]" << std::endl
        << "[" << setw(6) << m[8] << "][" << setw(6) << m[9] << "][" << setw(6) << m[10] << "][" << setw(6) << m[11] <<
        "]" << std::endl
        << "[" << setw(6) << m[12] << "][" << setw(6) << m[13] << "][" << setw(9) << m[14] << "][" << setw(6) << m[15]
        << "]" << std::endl
        << std::endl;
}
