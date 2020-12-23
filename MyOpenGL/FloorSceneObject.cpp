#include "FloorSceneObject.h"

constexpr auto FLOOR_SIZE = 10; // you want this to be greater or equal than zFar of the perspective projection;

std::vector<glm::vec3> FloorSceneObject::create_corners(float size)
{
    return vector<glm::vec3>{
        glm::vec3(-size, 0, +size),
        glm::vec3(+size, 0, +size),
        glm::vec3(+size, 0, -size),
        glm::vec3(-size, 0, -size),
    };
}

FloorSceneObject::FloorSceneObject(Shader shader) :
    SceneObject(
        QuadSurfaceSceneObject::generate_vertices(create_corners(FLOOR_SIZE)),
        QuadSurfaceSceneObject::generate_normals(create_corners(FLOOR_SIZE)),
        STATIC, 
        shader, 
        Material::create_night_floor())
{
    /*
    m_material = Material::create_texture("Models\\Floor.jpg", Material::create_default());
    auto f_texts = std::vector<float>{
        QuadSurfaceSceneObject::generate_texture_coordinates()
    };
    set_texture_coordinates(f_texts);
    */
}

void FloorSceneObject::draw(const Camera& camera, const glm::mat4& projection, const SceneLights& lights)
{
    const auto cam_pos = camera.get_position();
    m_transformation = Transform3D().translate(cam_pos.x, 0.0f, cam_pos.z);

    // run base class code
    SceneObject::draw(camera, projection, lights);
}
