#pragma once

#include <ostream>
#include "Vector3.h"

class Vector4
{
public:

    // static
    const static Vector4& empty();
    const static Vector4& identity();

    // instance

    // constructors
    Vector4();
    Vector4(const Vector4& from);
    Vector4(const Vector3& v3, float w);
    Vector4(float x, float y, float z, float w);
    explicit Vector4(float v[]); // non converting constructor

    //getters
    float x() const { return m_Array[0]; }
    float y() const { return m_Array[1]; }
    float z() const { return m_Array[2]; }
    float w() const { return m_Array[3]; }
    float get(const int i) const { return m_Array[i]; }

    //methods

    // operators
    float& operator[](const int i) { return m_Array[i]; }
    const float& operator[](const int i) const { return m_Array[i]; }
    friend std::ostream& operator<<(std::ostream& out, const Vector4& v);

private:

    float m_Array[4];
};
