#pragma once
#include <vector>

#include "SceneLights.h"
#include "SceneObject.h"

class SceneShadows {

public:

    SceneShadows(const SceneLights& lights);
    void compute(std::vector<SceneObject*>& objects);

private:

    void render_scene(std::vector<SceneObject*>& objects);
    void configure_shader();

    const SceneLights& m_lights;

    GLuint m_fbo;       // frame buffer object ID
    GLuint m_depthMap;  // texture ID
    Shader m_shader;
};

