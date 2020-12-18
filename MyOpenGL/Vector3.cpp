#include "Vector3.h"

const Vector3& Vector3::empty()
{
    float array[] = {0, 0, 0};

    static auto s_Vector3_Empty = Vector3{array};

    return s_Vector3_Empty;
}

const Vector3& Vector3::identity()
{
    float array[] = {1, 1, 1};

    static auto s_Vector3_Empty = Vector3{array};

    return s_Vector3_Empty;
}

Vector3::Vector3() : m_Array{0, 0, 0}
{
}

Vector3::Vector3(const Vector3& from) // NOLINT(cppcoreguidelines-pro-type-member-init)
{
    std::copy_n(from.m_Array, 3, m_Array);
}

Vector3::Vector3(const float x, const float y, const float z) // NOLINT(cppcoreguidelines-pro-type-member-init)
{
    m_Array[0] = x;
    m_Array[1] = y;
    m_Array[2] = z;
}

Vector3::Vector3(float v[]) // NOLINT(cppcoreguidelines-pro-type-member-init)
{
    std::copy_n(v, 3, m_Array);
}

float Vector3::get_length() const
{
    return std::sqrt(m_Array[0] * m_Array[0] + m_Array[1] * m_Array[1] + m_Array[2] * m_Array[2]);
}

Vector3 Vector3::get_normalize() const
{
    Vector3 v(*this);
    v.normalize();
    return v; // returns by copy
}

float Vector3::dot(const Vector3& other) const
{
    return
        m_Array[0] * other.m_Array[0] +
        m_Array[1] * other.m_Array[1] +
        m_Array[2] * other.m_Array[2];
}

Vector3& Vector3::normalize()
{
    const auto len = get_length();
    if (len != 0)
    {
        m_Array[0] /= len;
        m_Array[1] /= len;
        m_Array[2] /= len;
    }
    return *this;
}

Vector3& Vector3::move(float dx, float dy, float dz)
{
    m_Array[0] += dx;
    m_Array[1] += dy;
    m_Array[2] += dz;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
    return out << "x=" << v.x() << "; y=" << v.y() << "; z=" << v.z() << ";" << std::endl;
}
