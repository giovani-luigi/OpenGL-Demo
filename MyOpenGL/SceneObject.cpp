#include "SceneObject.h"


SceneObject::SceneObject(const std::vector<float>& vertices, const std::vector<float>& normals, Shader shader, SceneObjectType type)
	: m_vertices(vertices), m_vao(0), m_normals(normals)
{
	// create the VBO and assign the VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	
	// create vertex buffer object for attribute: positions
	GLuint vboPositions;
	glGenBuffers(1, &vboPositions); // create 1 buffer

	glBindBuffer(GL_ARRAY_BUFFER, vboPositions); // TODO: REMOVE THIS AND USE VAO ?
	
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], type);
		
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // setup the layout of the buffer
	glEnableVertexAttribArray(0); // enable the attribute

	m_shader = shader;
}

void SceneObject::draw(const Camera& camera, const glm::mat4& projection)
{
	// use specified shader for this object
	m_shader.use();

	// update uniforms (after binding the correct shader)
	m_shader.setMat4("view", camera.get_matrix()); // camera matrix
	m_shader.setMat4("proj", projection); // projection matrix
	m_shader.setMat4("model", m_transformation.get_matrix());
		
	//SetMaterial(ColorRGB(0, 0, 0), ColorRGB(0, 0, 0), ColorRGB(0, 0, 0));
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, (m_vertices.size() / 3) );
		
}
