#include "Shader.h"

GLuint Shader::createShaders(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLuint program = glCreateProgram();

    GLuint vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    GLuint fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    int linkerResult;
    glGetProgramiv(program, GL_LINK_STATUS, &linkerResult);
    if (linkerResult == GL_FALSE)
    {
        int len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
        auto message = (char*)malloc(sizeof(char) * len);
        glGetProgramInfoLog(program, len, &len, message);
        std::cout << "Failed to link shader." << std::endl;
        std::cout << message << std::endl;
        glDeleteProgram(program);
    }
    else
    {
        glValidateProgram(program);
    }

    // remove intermediary objects (*.obj)
    glDeleteShader(vs);
    glDeleteShader(fs);

    std::cout << "Shader created (Program ID=" << program << ")." << std::endl;

    return program;
}

GLuint Shader::compileShader(const std::string& code, GLenum type)
{
    auto id = glCreateShader(type);

    const char* src = &code[0];
    glShaderSource(id, 1, &src, nullptr); // null terminated string requires no length parameter
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        auto message = (char*)malloc(sizeof(char) * len);
        glGetShaderInfoLog(id, len, &len, message);
        std::cout << "Failed to compile shader." << std::endl;
        std::cout << message << std::endl;
    }

    return id;
}

Shader::Shader() : ID(0)
{
}

void Shader::dispose()
{
    if (ID != 0)
        glDeleteProgram(ID);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open("Shaders\\" + std::string(vertexPath));
        fShaderFile.open("Shaders\\" + std::string(fragmentPath));
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        ID = 1; // signal to create shaders
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        ID = 0;
    }

    // 2. compile shaders and get/assign to class' program ID
    if (ID == 1)
        ID = createShaders(vertexCode, fragmentCode);
}
