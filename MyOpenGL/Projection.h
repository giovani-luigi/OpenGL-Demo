#pragma once
#include "Matrix4x4.h"

class Projection
{
public:

    static Projection CreateEmpty()
    {
        Projection p;
        return p;
    }

    static Projection CreatePerspective(float fovY, float aspect, float zNear = 0.1f, float zFar = 100.0f)
    {
        Projection p;

        p.m_matrix.set(0, 0, 1.0f / (tan(fovY / 2) * aspect));
        p.m_matrix.set(1, 1, 1.0f / tan(fovY / 2));
        p.m_matrix.set(2, 2, (zFar + zNear) / (zNear - zFar));
        p.m_matrix.set(2, 3, (2 * zFar * zNear) / (zNear - zFar));
        p.m_matrix.set(3, 2, -1.0f);

        return p; // copy value return optimization will remove this extra copy
    }


    static Projection CreateParallel(
        float zNear, float zFar,
        float xLeft, float xRight,
        float yTop, float yBottom)
    {
        Projection p;

        p.m_matrix.set(0, 0, 2.0f / (xRight - xLeft));
        p.m_matrix.set(1, 1, 2.0f / (yTop - yBottom));
        p.m_matrix.set(2, 2, -2.0f / (zFar - zNear));
        p.m_matrix.set(3, 3, 1);
        p.m_matrix.set(0, 3, -(xRight + xLeft) / (xRight - xLeft));
        p.m_matrix.set(1, 3, -(yTop + yBottom) / (yTop - yBottom));
        p.m_matrix.set(2, 3, -(zFar + zNear) / (zFar - zNear));

        return p; // copy value return optimization will remove this extra copy
    }

    const Matrix4x4& get_matrix() const { return m_matrix; }

private:

    explicit Projection() : m_matrix(Matrix4x4::identity())
    {
    }

    Matrix4x4 m_matrix;
};
