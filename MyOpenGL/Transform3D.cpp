#include "Transform3D.h"

const Transform3D& Transform3D::empty()
{
    auto static empty = Transform3D();
    return empty;
}

Transform3D Transform3D::rotation_x(const float radians)
{
    const auto mx = rotate(glm::mat4(1.0f), radians, glm::vec3(1., 0., 0.));
    return Transform3D{mx};
}

Transform3D Transform3D::rotation_y(float radians)
{
    const auto mx = rotate(glm::mat4(1.0f), radians, glm::vec3(0., 1., 0.));
    return Transform3D{mx};
}

Transform3D Transform3D::rotation_z(float radians)
{
    const auto mx = rotate(glm::mat4(1.0f), radians, glm::vec3(0., 0., 1.));
    return Transform3D{mx};
}

Transform3D Transform3D::translation(float dx, float dy, float dz)
{
    const auto mx = glm::translate(glm::mat4(1.0f), glm::vec3(dx, dy, dz));
    return Transform3D{mx};
}

Transform3D Transform3D::scaling(float x, float y, float z)
{
    const auto mx = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
    return Transform3D{mx};
}

Transform3D::Transform3D() : m_matrix(1.0)
{
}

Transform3D::Transform3D(const glm::mat4& matrix) : m_matrix(matrix)
{
}

Transform3D& Transform3D::combine(const Transform3D& transformation)
{
    m_matrix = m_matrix * transformation.m_matrix;
    return *this;
}


glm::vec3 Transform3D::transform(const glm::vec3& v) const
{
    const auto v4 = m_matrix * glm::vec4(v, 1);
    return glm::vec3(v4.x, v4.y, v4.z);
}
