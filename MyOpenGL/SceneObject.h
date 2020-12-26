#pragma once
#include <vector>
#include <GL/glew.h>
#include "Transform3D.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "SceneLights.h"
#include "Texture.h"

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

    virtual void configure(const Camera& camera, const glm::mat4& projection, const SceneLights& lights);
    virtual void draw();
        
    void set_texture_coordinates(std::vector<float>& coordinates);
    bool has_texture() const { return !m_texcoordinates.empty(); }
    Transform3D& get_transformation() { return m_transformation; }
    GLuint get_vertex_buffer_id() const { return m_vbo; }
    Shader& get_shader() { return m_shader; }
    const std::vector<float>& get_vertices() const { return m_vertices; }
    GLuint get_vao() const { return m_vao; }

    bool FollowsCamera;
    bool DrawShadows;

protected:

    Transform3D m_transformation;
    Material m_material;
    Shader m_shader;

private:

    GLuint m_vao;
    GLuint m_vbo;   // buffer for vertex position
    GLuint m_nvbo;  // buffer for vertex normal
    GLuint m_tvbo;  // buffer for vertex texture

    std::vector<float> m_vertices;
    std::vector<float> m_normals;
    std::vector<float> m_texcoordinates;
};
