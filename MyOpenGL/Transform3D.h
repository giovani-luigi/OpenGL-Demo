#pragma once

#include "MathUtils.h"
#include "GLM/glm.hpp"
#include "GLM/fwd.hpp"
#include "GLM/ext/matrix_transform.hpp"

class Transform3D
{
public:

    // static

    const static Transform3D& empty();
    static Transform3D rotation_x(float radians);
    static Transform3D rotation_y(float radians);
    static Transform3D rotation_z(float radians);
    static Transform3D translation(float dx, float dy, float dz);
    static Transform3D scaling(float x, float y, float z);

    // instance

    // ctors	
    Transform3D();
    explicit Transform3D(const glm::mat4& matrix);

    // getters
    const float* get_array() const { return &m_matrix[0][0]; }
    const glm::mat4& get_matrix() const { return m_matrix; }

    // methods
    Transform3D& combine(const Transform3D& transformation);
    glm::vec3 transform(const glm::vec3& v) const;

    Transform3D& translate(float dx, float dy, float dz) { return combine(translation(dx, dy, dz)); }
    Transform3D& scale(float x, float y, float z) { return combine(scaling(x, y, z)); }
    Transform3D& rotate_x(float radians) { return combine(rotation_x(radians)); }
    Transform3D& rotate_y(float radians) { return combine(rotation_y(radians)); }
    Transform3D& rotate_z(float radians) { return combine(rotation_z(radians)); }

    Transform3D& rotate_x_deg(float degrees) { return combine(rotation_x(MathUtils::deg_to_rad(degrees))); }
    Transform3D& rotate_y_deg(float degrees) { return combine(rotation_y(MathUtils::deg_to_rad(degrees))); }
    Transform3D& rotate_z_deg(float degrees) { return combine(rotation_z(MathUtils::deg_to_rad(degrees))); }

private:

    glm::mat4 m_matrix = glm::mat4();
};
