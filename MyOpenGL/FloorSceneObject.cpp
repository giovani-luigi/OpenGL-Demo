#include "FloorSceneObject.h"

FloorSceneObject::FloorSceneObject(Shader shader) :
    SceneObject(
        QuadSurfaceSceneObject::generate_vertices(vector<glm::vec3>{
            glm::vec3(-1, 0, +1),
            glm::vec3(+1, 0, +1),
            glm::vec3(+1, 0, -1),
            glm::vec3(-1, 0, -1),
        }),
        QuadSurfaceSceneObject::generate_normals(vector<glm::vec3>{
            glm::vec3(-1, 0, +1),
            glm::vec3(+1, 0, +1),
            glm::vec3(+1, 0, -1),
            glm::vec3(-1, 0, -1),
        }),
        STATIC, 
        shader, 
        Material::create_night_floor())
{
}

void FloorSceneObject::draw(const Camera& camera, const glm::mat4& projection, const SceneLights& lights)
{
    const auto cam_pos = camera.get_position();
    m_transformation = Transform3D().translate(cam_pos.x, 0.0f, cam_pos.z).scale(100, 100, 100);

    // run base class code
    SceneObject::draw(camera, projection, lights);
}
