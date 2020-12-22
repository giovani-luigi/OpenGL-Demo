#pragma once
#include "CubeSceneObject.h"

class SkyBoxSceneObject : public CubeSceneObject {

public:

    SkyBoxSceneObject(
        const string& directoryPath, 
        const string& posXFilename, 
        const string& negXFilename, 
        const string& posYFilename,
        const string& negYFilename, 
        const string& posZFilename, 
        const string& negZFilename);

    void draw(const Camera& camera, const glm::mat4& projection, const SceneLights& lights) override;
    
private:

    GLuint m_skybox_texture_id;

    std::vector<std::string> m_texture_files;

    //Cube Map Texture Object Target
    GLenum  m_cubeMapTarget[6] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

};