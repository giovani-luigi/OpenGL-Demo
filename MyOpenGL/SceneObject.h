#pragma once
#include <vector>
#include <GL/glew.h>
#include "Transform3D.h"
#include "Camera.h"
#include "Shader.h"

class SceneObject {

public:

	SceneObject(const std::vector<float>& vertices, const std::vector<float>& normals, Shader shader);

	void draw(const Camera& camera, const glm::mat4& projection) const;

	// gets the transformation to be used by the shader
	Transform3D& get_transformation() { return m_transformation; }	

	Shader get_custom_shader() const { return m_shader; }

	void set_custom_shader(Shader shader) { m_shader = shader; }
	
private:

	GLuint m_vao;

	Transform3D m_transformation;
	Shader m_shader;

	const std::vector<float> m_vertices;
	const std::vector<float> m_normals;
};

