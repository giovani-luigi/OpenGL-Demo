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
            glm::vec3(0.5f, 0.5f, 0.5f),
            1.0f,
            0.02f,
            0.01f
        );
    }

    static SceneLights create_night(const Camera& camera)
    {
        // creates a light, somewhere near the moon's position
        // with no decay because our light source tries to mimic the moon at skybox
        // which in turn is 'constant' to the scene.
        return SceneLights(camera,
            glm::vec3(-5.0f, 5.0f, 3.0f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(0.52f, 0.45f, 0.6f),
            glm::vec3(0.3f, 0.3f, 0.45f),
            1.0f,  
            0.00f,
            0.00f
        );
    }

    // fields
    glm::vec3 position;
    glm::vec3 specular;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    float decay_constant;
    float decay_linear;
    float decay_quadratic;

    // methods
    void set_uniforms(Shader& shader) const {
        const auto l_pos = m_camera.get_matrix() * glm::vec4(position, 1.0); // put light in view space
        shader.use();
        shader.setVec3("u_light.position", l_pos.x, l_pos.y, l_pos.z); // light position in view space
        shader.setVec3("u_light.specular", specular.r, specular.g, specular.b); // light specular emission
        shader.setVec3("u_light.diffuse", diffuse.r, diffuse.g, diffuse.b); // light diffuse emission
        shader.setVec3("u_light.ambient", ambient.r, ambient.g, ambient.b); // light ambient emission

        shader.setFloat("u_light.decayConstant", decay_constant); // light decay constant coefficient
        shader.setFloat("u_light.decayLinear", decay_linear); // light decay linear coefficient
        shader.setFloat("u_light.decayQuadratic", decay_quadratic); // light decay quadratic coefficient
    }

private:

    const Camera& m_camera;

    // constructor
    SceneLights(
        const Camera& camera,
        glm::vec3 position,
        glm::vec3 specular,
        glm::vec3 diffuse,
        glm::vec3 ambient,
        float decayConstant,
        float decayLinear,
        float decayQuadratic
    ) :
        position(position),
        specular(specular),
        diffuse(diffuse),
        ambient(ambient),
        decay_constant(decayConstant),
        decay_linear(decayLinear),
        decay_quadratic(decayQuadratic),
        m_camera(camera)
    {
    }
};