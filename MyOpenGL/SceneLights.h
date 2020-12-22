#pragma once

#include "Camera.h"
#include "Shader.h"

class SceneLights {

public:

    // factory methods
    static SceneLights create_default(const Camera& camera)
    {
        return SceneLights(camera,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.17f, 0.15f, 0.12f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(0.5f, 0.5f, 0.5f)
        );
    }

    static SceneLights create_night(const Camera& camera)
    {
        // creates a light, somewhere near the moon's position
        return SceneLights(camera,
            glm::vec3(-5.0f, 5.0f, 5.0f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(0.52f, 0.45f, 0.6f),
            glm::vec3(0.3f, 0.3f, 0.45f)
        );
    }

    // fields
    const Camera& m_camera;
    glm::vec3 position;
    glm::vec3 specular;
    glm::vec3 diffuse;
    glm::vec3 ambient;

    // constructor
    SceneLights(
        const Camera& camera,
        glm::vec3 position,
        glm::vec3 specular,
        glm::vec3 diffuse,
        glm::vec3 ambient
        ) : m_camera(camera), position(position), specular(specular), diffuse(diffuse), ambient(ambient)
    {
    }

    // methods
    void set_uniforms(Shader& shader) const
    {
        const auto l_pos = m_camera.get_matrix() * glm::vec4(position, 1.0); // put light in view space
        shader.use();
        shader.setVec3("u_light.position", l_pos.x, l_pos.y, l_pos.z); // light position in view space
        shader.setVec3("u_light.specular", specular.r, specular.g, specular.b); // light specular emission
        shader.setVec3("u_light.diffuse", diffuse.r, diffuse.g, diffuse.b); // light diffuse emission
        shader.setVec3("u_light.ambient", ambient.r, ambient.g, ambient.b); // light ambient emission
    }
};