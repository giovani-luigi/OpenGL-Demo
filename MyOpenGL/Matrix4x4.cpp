#include "Matrix4x4.h"

const Matrix4x4& Matrix4x4::empty()
{
    float array[16] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };

    static auto s_MxEmpty = Matrix4x4{array};

    return s_MxEmpty;
}

const Matrix4x4& Matrix4x4::identity()
{
    float array[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };

    static auto s_MxIdentity = Matrix4x4{array};

    return s_MxIdentity;
}

Matrix4x4::Matrix4x4() :
    m_Array{
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    }
{
}

Matrix4x4::Matrix4x4(float v[]) :
    m_Array{
        v[0], v[1], v[2], v[3],
        v[4], v[5], v[6], v[7],
        v[8], v[9], v[10], v[11],
        v[12], v[13], v[14], v[15],
    }
{
}

// copy constructor
Matrix4x4::Matrix4x4(const Matrix4x4& from) // NOLINT(cppcoreguidelines-pro-type-member-init)
{
    std::copy_n(from.m_Array, 16, m_Array);
}

void Matrix4x4::transpose()
{
    float t;
    t = m_Array[1];
    m_Array[1] = m_Array[4];
    m_Array[4] = t;
    t = m_Array[2];
    m_Array[2] = m_Array[8];
    m_Array[8] = t;
    t = m_Array[3];
    m_Array[3] = m_Array[12];
    m_Array[12] = t;
    t = m_Array[6];
    m_Array[6] = m_Array[9];
    m_Array[9] = t;
    t = m_Array[7];
    m_Array[7] = m_Array[13];
    m_Array[13] = t;
    t = m_Array[11];
    m_Array[11] = m_Array[14];
    m_Array[14] = t;
}


Matrix4x4 Matrix4x4::get_transpose() const
{
    Matrix4x4 m(*this);
    m.transpose();
    return m; // returns by copy
}

void Matrix4x4::make_identity()
{
    std::copy_n(identity().m_Array, 16, m_Array);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
{
    Matrix4x4 m;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[(4 * i) + j] = 0.0;
            for (int k = 0; k < 4; k++)
            {
                m[(4 * i) + j] += m_Array[(4 * i) + k] * other.get((4 * k) + j);
            }
        }
    }
    return m; // copy
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const
{
    Matrix4x4 m;
    for (int i = 0; i < 16; i++)
    {
        m[i] = get(i) + other.get(i);
    }
    return m; // copy
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const
{
    Matrix4x4 m;
    for (int i = 0; i < 16; i++)
    {
        m[i] = get(i) - other.get(i);
    }
    return m; // copy
}

Vector4 Matrix4x4::operator*(const Vector4& v) const
{
    return Vector4(
        get(0, 0) * v.x() + get(0, 1) * v.y() + get(0, 2) * v.z() + get(0, 3) * v.w(),
        get(1, 0) * v.x() + get(1, 1) * v.y() + get(1, 2) * v.z() + get(1, 3) * v.w(),
        get(2, 0) * v.x() + get(2, 1) * v.y() + get(2, 2) * v.z() + get(2, 3) * v.w(),
        get(3, 0) * v.x() + get(3, 1) * v.y() + get(3, 2) * v.z() + get(3, 3) * v.w()
    );
}

Matrix4x4& Matrix4x4::operator*(const float scale)
{
    for (int i = 0; i < 16; i++)
    {
        m_Array[i] *= scale;
    }
    return *this;
}

Matrix4x4& Matrix4x4::operator/(const float scale)
{
    for (int i = 0; i < 16; i++)
    {
        m_Array[i] /= scale;
    }
    return *this;
}
