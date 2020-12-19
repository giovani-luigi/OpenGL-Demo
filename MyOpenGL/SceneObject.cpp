#include "SceneObject.h"


SceneObject::SceneObject(const std::vector<float>& vertices, const std::vector<float>& normals, Shader shader,
                         SceneObjectType type)
    : m_vertices(vertices), m_vao(0), m_normals(normals)
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
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(float), &m_normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // setup the layout of the buffer for positions
    glEnableVertexAttribArray(1); // enable the attribute

    m_shader = shader;
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
    m_shader.setVec3("u_material.specular",     1.0f, 1.0f, 1.0f); // material specular reflection
    m_shader.setVec3("u_material.diffuse",      0.5f, 0.5f, 0.5f); // material diffuse reflection
    m_shader.setVec3("u_material.ambient",      0.2f, 0.2f, 0.2f); // material ambient reflection
    m_shader.setFloat("u_material.shininess",   32);
    m_shader.setVec3("u_light.position",        0.0f, 0.5f, 0.5f); // light position in view space
    m_shader.setVec3("u_light.specular",        0.1f, 0.0f, 0.0f); // light specular emission
    m_shader.setVec3("u_light.diffuse",         1.0f, 1.0f, 1.0f); // light diffuse emission
    m_shader.setVec3("u_light.ambient",         0.2f, 0.2f, 0.2f); // light ambient emission

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, (m_vertices.size() / 3));
    
}

