#pragma once
#include "SceneLights.h"

class SceneShadows {

public:

    SceneShadows(const SceneLights& lights);
    void draw();

private:

    const SceneLights& m_lights;

};

