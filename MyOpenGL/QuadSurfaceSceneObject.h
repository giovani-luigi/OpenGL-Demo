#pragma once
#include "SceneObject.h"

class QuadSurfaceSceneObject : public SceneObject {
		
public:

	explicit QuadSurfaceSceneObject(const std::vector<glm::vec3>& corners, Shader shader, SceneObjectType type) :
		SceneObject(generate_vertices(corners), generate_normals(corners), shader, type)
	{		
	}

	static std::vector<float> generate_vertices(const std::vector<glm::vec3>& corners)
	{
		// create two triangles based on the corners
		return std::vector<float> {
			// first, upper right triangle
			corners[0].x, corners[0].y, corners[0].z,
			corners[1].x, corners[1].y, corners[1].z,
			corners[2].x, corners[2].y, corners[2].z,
			// second, bottom left triangle
			corners[2].x, corners[2].y, corners[2].z,
			corners[3].x, corners[3].y, corners[3].z,
			corners[0].x, corners[0].y, corners[0].z,
		};
	}

	static std::vector<float> generate_normals(const std::vector<glm::vec3>& corners)
	{
		// 1. calculate the face's normal:

		// get two corners, and get the cross product between them, to obtain the normal
		glm::vec3 u = corners[1] - corners[0];
		glm::vec3 v = corners[2] - corners[0];
		auto normal = glm::normalize(glm::cross(u, v));

		// 2. return all vertices with that same normal (we can optimize this... no time now)
		return std::vector<float> {
			// first, upper right triangle
			normal.x, normal.y, normal.z,
			normal.x, normal.y, normal.z,
			normal.x, normal.y, normal.z,
			// second, bottom left triangle
			normal.x, normal.y, normal.z,
			normal.x, normal.y, normal.z,
			normal.x, normal.y, normal.z,
		};
	}
	
};

