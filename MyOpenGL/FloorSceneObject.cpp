#include "FloorSceneObject.h"

FloorSceneObject::FloorSceneObject(Shader shader) :
    SceneObject(
        QuadSurfaceSceneObject::generate_vertices(vector<glm::vec3>{
            glm::vec3(-100, 0, +100),
            glm::vec3(+100, 0, +100),
            glm::vec3(+100, 0, -100),
            glm::vec3(-100, 0, -100),
        }),
        QuadSurfaceSceneObject::generate_normals(vector<glm::vec3>{
            glm::vec3(-100, 0, +100),
            glm::vec3(+100, 0, +100),
            glm::vec3(+100, 0, -100),
            glm::vec3(-100, 0, -100),
        }),
        STATIC, 
        shader, 
        Material::create_night_floor())
{
   // m_material = Material::create_texture()
   
}

void FloorSceneObject::draw(const Camera& camera, const glm::mat4& projection, const SceneLights& lights)
{
    const auto cam_pos = camera.get_position();
    m_transformation = Transform3D().translate(cam_pos.x, 0.0f, cam_pos.z);

    // run base class code
    SceneObject::draw(camera, projection, lights);
}
