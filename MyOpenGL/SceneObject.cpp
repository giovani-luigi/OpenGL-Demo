#include "SceneObject.h"

#include <utility>


SceneObject::SceneObject(const std::vector<float>& vertices, const std::vector<float>& normals, SceneObjectType type, Shader shader, Material material) :
    m_vao(0), m_material(material), m_shader(shader), m_texture(), m_vertices(vertices), m_normals(normals)
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

    if (material.has_texture())
    {
        m_texels = material.get_texture_coordinates();

        // create vertex buffer object for attribute: texture
        glGenBuffers(1, &m_tvbo); // create 1 buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_tvbo);
        glBufferData(GL_ARRAY_BUFFER, m_texels.size() * sizeof(float), &m_texels[0], GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr); // setup the layout of the buffer for positions
        glEnableVertexAttribArray(2); // enable the attribute       
    }
    else
    {
        glDisableVertexAttribArray(2); // disable the texture coordinate attribute    
    }    
}

void SceneObject::draw(const Camera& camera, const glm::mat4& projection, const SceneLights& lights)
{
    // use specified shader for this object
    m_shader.use();

    // update uniforms for vertex shader
    m_shader.setMat4("u_view", camera.get_matrix()); // camera matrix
    m_shader.setMat4("u_proj", projection); // projection matrix
    m_shader.setMat4("u_model", m_transformation.get_matrix());

    // activate material
    m_material.use(m_shader);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, (m_vertices.size() / 3));
}