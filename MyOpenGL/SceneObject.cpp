#include "SceneObject.h"

SceneObject::SceneObject(const std::vector<float>& vertices, const std::vector<float>& normals, SceneObjectType type, Shader shader, Material material) :
    m_vao(0), m_material(material), m_shader(shader), m_vertices(vertices), m_normals(normals)
{
    // create the VBO and assign the VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // create vertex buffer object for attribute: positions
    glGenBuffers(1, &m_vbo); // create 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], type);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // setup the layout of the buffer for positions
    glEnableVertexAttribArray(0); // enable the attribute

    // create vertex buffer object for attribute: normals
    glGenBuffers(1, &m_nvbo); // create 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_nvbo);
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(float), &m_normals[0], type);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // setup the layout of the buffer for positions
    glEnableVertexAttribArray(1); // enable the attribute
}

void SceneObject::draw(const Camera& camera, const glm::mat4& projection)
{
    // use specified shader for this object
    m_shader.use();

    // update uniforms for vertex shader
    m_shader.setMat4("u_view", camera.get_matrix()); // camera matrix
    m_shader.setMat4("u_proj", projection); // projection matrix
    m_shader.setMat4("u_model", m_transformation.get_matrix());

    // update uniforms for fragment shader

    glm::vec3 light_pos(0.0f, 0.5f, 0.5f); // light position in the scene
    auto l_pos = camera.get_matrix() * glm::vec4(light_pos, 1.0); // put light in view space

    m_shader.setVec3("u_light.position", l_pos.x, l_pos.y, l_pos.z); // light position in view space
    m_shader.setVec3("u_light.specular", 0.2f, 0.2f, 0.1f); // light specular emission
    m_shader.setVec3("u_light.diffuse", 1.0f, 1.0f, 1.0f); // light diffuse emission
    m_shader.setVec3("u_light.ambient", 0.5f, 0.5f, 0.5f); // light ambient emission
    
    m_material.set_uniforms(m_shader);
    
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, (m_vertices.size() / 3));
    
}

