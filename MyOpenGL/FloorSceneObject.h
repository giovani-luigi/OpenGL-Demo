#pragma once

#include "SceneObject.h"
#include "QuadSurfaceSceneObject.h"

class FloorSceneObject : public SceneObject
{
public:

    FloorSceneObject(const Camera& camera, Shader shader);

    void draw(const Camera& camera, const glm::mat4& projection) override;


private:

    const Camera& m_camera;
};
