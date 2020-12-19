#include "Material.h"

Material::Material(const glm::vec3& specular, const glm::vec3& diffuse, const glm::vec3& ambient, float shininess) :
    specular(specular),
    diffuse(diffuse),
    ambient(ambient),
    shininess(shininess) {
}

void Material::set_uniforms(Shader& shader)
{
    shader.use();
    shader.setVec3("u_material.specular", specular.r, specular.g, specular.b); // material specular reflection
    shader.setVec3("u_material.diffuse", diffuse.r, diffuse.g, diffuse.b); // material diffuse reflection
    shader.setVec3("u_material.ambient", ambient.r, ambient.g, ambient.b); // material ambient reflection
    shader.setFloat("u_material.shininess", shininess);
}

Material Material::create_white_marble()
{
    return Material(
        glm::vec3(1.0f, 0.97f, 0.98f),
        glm::vec3(0.5f, 0.45f, 0.38f),
        glm::vec3(0.75f, 0.75f, 0.75f),
        32
    );
}

Material Material::create_brown_floor()
{
    return Material(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.2f, 0.12f, 0.1f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        0
    );
}
