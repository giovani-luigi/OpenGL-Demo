#pragma once

#include "SceneObject.h"
#include "QuadSurfaceSceneObject.h"

class FloorSceneObject : public SceneObject
{
public:

    FloorSceneObject(Shader shader);

    void draw(const Camera& camera, const glm::mat4& projection, const SceneLights& lights) override;


private:

    static std::vector<glm::vec3> create_corners(float size);

};
