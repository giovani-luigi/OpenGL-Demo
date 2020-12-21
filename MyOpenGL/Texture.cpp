#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"

Texture::Texture() : m_texture(0), m_width(0), m_height(0)
{
}

Texture::Texture(const std::string& filePath, bool flip_vertically)
{
    glGenTextures(1, &m_texture);

    stbi_set_flip_vertically_on_load(flip_vertically);

    int w, h, nComponents; // nComponents : R/RGB/RGBA...
    uint8_t * pixels = stbi_load(filePath.c_str(), &w, &h, &nComponents, 4);

    if (pixels == nullptr) 
    {
        std::cout << "TEXTURE::ERROR::FAILED_TO_LOAD_FILE('" << filePath << "')" << std::endl;
        m_texture = 0;
        return;
    }

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D); // tell opengl to generate all mip maps automatically, 

    stbi_image_free(pixels);

    m_height = h;
    m_width = w;
}

void Texture::dispose()
{
    if (m_texture != 0)
        glDeleteTextures(1, &m_texture);
}

void Texture::use(int unit) const
{
    if (m_texture != 0)
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }    
}


