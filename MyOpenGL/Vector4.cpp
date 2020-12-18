#include "Vector4.h"

const Vector4& Vector4::empty()
{
    float array[] = {0, 0, 0, 0};

    static auto s_Vector4_Empty = Vector4{array};

    return s_Vector4_Empty;
}

const Vector4& Vector4::identity()
{
    float array[] = {1, 1, 1, 1};

    static auto s_Vector4_Empty = Vector4{array};

    return s_Vector4_Empty;
}

Vector4::Vector4() : m_Array{0, 0, 0, 0}
{
}

Vector4::Vector4(float v[]) : m_Array{v[0], v[1], v[2], v[3]}
{
}

// copy constructor
Vector4::Vector4(const Vector4& from) // NOLINT(cppcoreguidelines-pro-type-member-init)
{
    std::copy_n(from.m_Array, 4, m_Array);
}

Vector4::Vector4(const Vector3& v3, const float w) : m_Array{v3.get(0), v3.get(1), v3.get(2), w}
{
}

Vector4::Vector4(const float x, const float y, const float z, const float w) : m_Array{x, y, z, w}
{
}

std::ostream& operator<<(std::ostream& out, const Vector4& v)
{
    return out << "x=" << v.x() << "; y=" << v.y() << "; z=" << v.z() << "; w=" << v.w() << std::endl;
}
