#pragma once

#include "SceneObject.h"
#include "QuadSurfaceSceneObject.h"

class FloorSceneObject : public SceneObject
{
public:

    FloorSceneObject(Shader shader);

    void configure(const Camera& camera, const glm::mat4& projection, const SceneLights& lights) override;
    void draw() override;

private:

    static std::vector<glm::vec3> create_corners(float size);

    float m_row;
    float m_col;

    const Camera * m_camera;
    const glm::mat4 * m_projection;
    const SceneLights * m_lights;

};
