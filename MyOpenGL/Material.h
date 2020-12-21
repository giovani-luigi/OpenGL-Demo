#pragma once

#include <vector>

#include "Shader.h"
#include "Texture.h"

class Material
{

public:

    // factory methods:
    static Material create_white_marble();
    static Material create_brown_floor();

    static Material create_texture(
        const vector<float>& coordinates, 
        const std::string& imagePath, 
        const glm::vec3& ambient, 
        const glm::vec3& diffuse,
        const glm::vec3& specular, 
        float shininess);

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


