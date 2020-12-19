#pragma once
#include <vector>
#include <GL/glew.h>
#include "Transform3D.h"
#include "Camera.h"
#include "Shader.h"

class SceneObject
{
public:

    enum SceneObjectType : GLuint
    {
        STATIC = GL_STATIC_DRAW,
        DYNAMIC = GL_DYNAMIC_DRAW
    };

    SceneObject(const std::vector<float>& vertices, const std::vector<float>& normals, Shader shader,
                SceneObjectType type);
    virtual ~SceneObject() = default;

    virtual void draw(const Camera& camera, const glm::mat4& projection);

    // gets the transformation to be used by the shader
    Transform3D& get_transformation() { return m_transformation; }

    Shader get_custom_shader() const { return m_shader; }
    GLuint get_vertex_buffer_id() const { return m_vbo; }

    void set_custom_shader(Shader shader) { m_shader = shader; }

protected:

    GLuint m_vao;
    GLuint m_vbo;

    Transform3D m_transformation;
    Shader m_shader;

    std::vector<float> m_vertices;
    std::vector<float> m_normals;
};
