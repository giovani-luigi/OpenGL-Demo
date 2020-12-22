#pragma once

#include <vector>

#include "Shader.h"
#include "Texture.h"

class Material
{

public:

    // factory methods:
    static Material create_default();
    static Material create_white_marble();
    static Material create_white_plastic();
    static Material create_brown_floor();
    static Material create_night_floor();
    static Material create_dark_grey_rock();
    static Material create_yellow_rock();

    static Material create_texture(
        const vector<float>& coordinates, 
        const std::string& imagePath, 
        const glm::vec3& ambient, 
        const glm::vec3& diffuse,
        const glm::vec3& specular, 
        float shininess);

    // getters
    const glm::vec3& get_specular_component() const { return m_specular; }
    const glm::vec3& get_diffuse_component() const { return m_diffuse; }
    const glm::vec3& get_ambient_component() const { return m_ambient; }
    float get_shininess() const { return m_shininess; }

    // methods
    void use(Shader& shader);
    bool has_texture() const { return !m_texcoordinates.empty(); }
    const std::vector<float>& get_texture_coordinates() const { return m_texcoordinates; }

private:

    // fields
    glm::vec3 m_specular;
    glm::vec3 m_diffuse;
    glm::vec3 m_ambient;
    float m_shininess;

    std::vector<float> m_texcoordinates;
    Texture m_texture;

    // constructors
    Material() = default;
    Material(const glm::vec3& specular, const glm::vec3& diffuse, const glm::vec3& ambient, float shininess = 0);

};


