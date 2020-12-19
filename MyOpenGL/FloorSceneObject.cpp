#include "FloorSceneObject.h"

FloorSceneObject::FloorSceneObject(const Camera& camera, Shader shader) :
    SceneObject(
        QuadSurfaceSceneObject::generate_vertices(vector<glm::vec3>{
            glm::vec3(-1, 0, +1),
            glm::vec3(+1, 0, +1),
            glm::vec3(+1, 0, -1),
            glm::vec3(-1, 0, -1),
        }),
        QuadSurfaceSceneObject::generate_normals(vector<glm::vec3>{
            glm::vec3(-1, 0, +1),
            glm::vec3(+1, 0, +1),
            glm::vec3(+1, 0, -1),
            glm::vec3(-1, 0, -1),
        }),
        shader, DYNAMIC),
    m_camera(camera)
{
}

void FloorSceneObject::draw(const Camera& camera, const glm::mat4& projection)
{
    // recalculate corners
    auto c = camera.get_position();
    float size = 1.0f;
    const auto corners = vector<glm::vec3>{
        glm::vec3(c.x - size, 0.0f, c.z + size),
        glm::vec3(c.x + size, 0.0f, c.z + size),
        glm::vec3(c.x + size, 0.0f, c.z - size),
        glm::vec3(c.x - size, 0.0f, c.z - size),
    };

    // update RAM buffer
    m_vertices = QuadSurfaceSceneObject::generate_vertices(corners);
    m_normals = QuadSurfaceSceneObject::generate_normals(corners);

    // update VRAM buffer
    glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer_id());
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(float), &m_vertices[0]);

    // run base class code
    SceneObject::draw(camera, projection);
}
