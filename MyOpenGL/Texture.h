#pragma once
#include <string>
#include <GL/glew.h>
#include <iostream>

class Texture {

public:

    explicit Texture();

    explicit Texture(const std::string& filePath, bool flip_vertically = false);
    void dispose();

    void use(int unit = 0) const;

private:

    GLuint m_texture;
    int m_width;
    int m_height;

};

