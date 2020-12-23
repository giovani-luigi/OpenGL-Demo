#pragma once
#include "CubeSceneObject.h"

class SkyBoxSceneObject : public CubeSceneObject {

public:

    SkyBoxSceneObject(
        const std::string& directoryPath, 
        const std::string& posXFilename, 
        const std::string& negXFilename, 
        const std::string& posYFilename,
        const std::string& negYFilename, 
        const std::string& posZFilename, 
        const std::string& negZFilename);

    void configure(const Camera& camera, const glm::mat4& projection, const SceneLights& lights) override;
    void draw() override;
    
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