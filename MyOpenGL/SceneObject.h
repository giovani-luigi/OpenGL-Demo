#pragma once
#include <vector>
#include <GL/glew.h>
#include "Transform3D.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "SceneLights.h"

class SceneObject
{
public:

    enum SceneObjectType : GLuint
    {
        STATIC = GL_STATIC_DRAW,
        DYNAMIC = GL_DYNAMIC_DRAW
    };

    SceneObject(const std::vector<float>& vertices, const std::vector<float>& normals, SceneObjectType type, Shader shader, Material material);
    virtual ~SceneObject() = default;

    virtual void draw(const Camera& camera, const glm::mat4& projection, const SceneLights& lights);

    // gets the transformation to be used by the shader
    Transform3D& get_transformation() { return m_transformation; }

    GLuint get_vertex_buffer_id() const { return m_vbo; }

    Shader& get_shader() { return m_shader; }


protected:

    GLuint m_vao;
    GLuint m_vbo{};   // buffer for vertex position
    GLuint m_nvbo{};  // buffer for vertex normal

    Transform3D m_transformation;
    Material m_material;
    Shader m_shader;

    std::vector<float> m_vertices;
    std::vector<float> m_normals;
};
