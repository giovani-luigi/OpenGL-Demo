#pragma once

#include "Shader.h"

class Material
{

public:

    // factory methods:
    static Material create_white_marble();
    static Material create_brown_floor();

    // methods
    void set_uniforms(Shader& shader);

private:

    // fields
    glm::vec3 specular;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    float shininess;

    // constructors
    Material() = default;
    Material(const glm::vec3& specular, const glm::vec3& diffuse, const glm::vec3& ambient, float shininess = 0);

};


