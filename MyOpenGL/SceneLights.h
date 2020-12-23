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

        shader.use();

        // main point light (moon)

        const auto l_pos = m_camera.get_matrix() * glm::vec4(position, 1.0); // put light in view space

        shader.setVec3("u_light.position", l_pos); // light position in view space
        shader.setVec3("u_light.specular", specular); // light specular emission
        shader.setVec3("u_light.diffuse", diffuse); // light diffuse emission
        shader.setVec3("u_light.ambient", ambient); // light ambient emission
        shader.setFloat("u_light.decayConstant", decay_constant); // light decay constant coefficient
        shader.setFloat("u_light.decayLinear", decay_linear); // light decay linear coefficient
        shader.setFloat("u_light.decayQuadratic", decay_quadratic); // light decay quadratic coefficient

        // flashlight

        // the flashlight's position is the same as camera's position for simplicity
        // notice that we need to put camera's position into view space because of rotations
        // also, the normal vector, needs to be placed in the view space, however NOTICE the
        // value of the 'w' component of the vec4 multiplication.

        const auto fl_pos = m_camera.get_matrix() * glm::vec4(m_camera.get_position(), 1.0f); // <<= w is One
        const auto fl_dir = m_camera.get_matrix() * glm::vec4(m_camera.get_front_direction(), 0.0f); // <<= w is Zero
        
        shader.setVec3("u_flashlight.position", fl_pos); // light position in view space
        shader.setVec3("u_flashlight.direction", fl_dir); 
        shader.setFloat("u_flashlight.decayConstant", 1.0f); // light decay constant coefficient
        shader.setFloat("u_flashlight.decayLinear", 0.5f); // light decay linear coefficient
        shader.setFloat("u_flashlight.decayQuadratic", 0.2f); // light decay quadratic coefficient
        shader.setFloat("u_flashlight.cutOff", glm::cos(glm::radians(12.0f))); // angle cossine where light starts to fade-out from the center of the cone
        shader.setFloat("u_flashlight.outerCutOff", glm::cos(glm::radians(15.0f))); // outer angle's cossine, so it makes a smooth transition
        shader.setVec3("u_flashlight.specular", glm::vec3(1.0f, 1.0f, 1.0f)); // light specular emission
        shader.setVec3("u_flashlight.diffuse", glm::vec3(0.3f, 0.32f, 0.26f)); // light diffuse emission
        shader.setVec3("u_flashlight.ambient", glm::vec3(0.5f, 0.5f, 0.5f)); // light ambient emission

        shader.setFloat("u_flashlight.brightness", m_flashlight_brightness); // the brightness (ON/OFF/dim...)

    }
        
    void toggle_flashlight() { m_flashlight_brightness = m_flashlight_brightness == 0.0f ? 1.0f : 0.0f; }

private:

    const Camera& m_camera;

    float m_flashlight_brightness;

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
        m_camera(camera),
        m_flashlight_brightness(0.0f)
    {
    }
};