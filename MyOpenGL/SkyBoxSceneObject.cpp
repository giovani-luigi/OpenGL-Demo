#include "SkyBoxSceneObject.h"

#include "CubeSceneObject.h"
#include "STB/stb_image.h"

SkyBoxSceneObject::SkyBoxSceneObject(
    const string& directoryPath,
    const string& posXFilename,
    const string& negXFilename,
    const string& posYFilename,
    const string& negYFilename,
    const string& posZFilename,
    const string& negZFilename) :
    CubeSceneObject(Shader("skybox.vertex.shader", "skybox.fragment.shader")),
    m_skybox_texture_id(0)
{
    m_texture_files.push_back(directoryPath + posXFilename);
    m_texture_files.push_back(directoryPath + negXFilename);
    m_texture_files.push_back(directoryPath + posYFilename);
    m_texture_files.push_back(directoryPath + negYFilename);
    m_texture_files.push_back(directoryPath + posZFilename);
    m_texture_files.push_back(directoryPath + negZFilename);

    glGenTextures(1, &m_skybox_texture_id);

    stbi_set_flip_vertically_on_load(true);

    glActiveTexture(GL_TEXTURE0);

    for (int i = 0; i < 6; i++)
    {
        int w, h, nComponents; // nComponents : R/RGB/RGBA...
        uint8_t* pixels = stbi_load(m_texture_files[i].c_str(), &w, &h, &nComponents, 4);

        if (pixels == nullptr) {
            std::cout << "TEXTURE::ERROR::FAILED_TO_LOAD_FILE('" << m_texture_files[i] << "')" << std::endl;
            exit(1);
        }

        glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox_texture_id);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(m_cubeMapTarget[i], 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        stbi_image_free(pixels);
    }
}

void SkyBoxSceneObject::draw(const Camera& camera, const glm::mat4& projection, const SceneLights& lights)
{
    // 1. use special shader for the skybox
    m_shader.use();

    const auto cam_pos = camera.get_position();
    m_transformation = Transform3D().translate(cam_pos.x, 0.5f, cam_pos.z); // skybox follows the camera in Z and X

    // 2. update uniforms for shaders
    m_shader.setMat4("u_view", camera.get_matrix()); // camera matrix
    m_shader.setMat4("u_proj", projection); // projection matrix
    m_shader.setMat4("u_model", m_transformation.get_matrix());

    m_shader.setInt("u_texture", 0); // set texture unit to 0

    // 3. draw the pixels if the incoming depth value is less than or equal to the stored depth value.
    glDepthFunc(GL_LEQUAL); 

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox_texture_id);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, (m_vertices.size() / 3));

    // 4. draw the pixels if the incoming depth value is less than the stored depth value
    glDepthFunc(GL_LESS);
    /*
     A skybox appears to always be rendered behind any other object in a scene. For this
     to occur we need to compare the incoming pixel-depth with the currently present in the frame buffer.
     In section 3 we use the depth test condition of _GLLEQUAL. This allows the skybox to be render behind
     any other object in the scene. Line 7 renders the skybox as usual. The depth condition is then set
     to the default condition of _GLLESS, which allows objects to be render in front of any other in the scene (section 4).
     */

}
