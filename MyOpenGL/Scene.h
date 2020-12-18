#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Debug.h"
#include "SceneObject.h"
#include "Shader.h"

#include <filesystem>

#include "Camera.h"
#include "CubeSceneObject.h"
#include "FileSceneObject.h"
#include "GLM/ext/matrix_clip_space.hpp"

class Scene
{
public:

    Scene(GLFWwindow* window);
    ~Scene();

    void run();
    void process_key(int keyCode, int scanCode, int action, int modifiers);
    void process_cursor(float xpos, float ypos);
    void process_viewport_resize(int width, int height);

private:

    GLFWwindow* m_window;
    std::vector<SceneObject> m_objects;
    Camera m_camera;
    glm::mat4 m_projection;
    double m_lastFrameTime;
    double m_deltaTime = 0;
    float m_mouse_x;
    float m_mouse_y;
    bool m_mouse_first;
    int m_frame;
    float m_mouse_sensitivity = 0.1f;
    float m_keyboard_speed = 2.5f;

    Shader create_global_shader();
    Shader create_light_shader();

    void update_shaders();
    void setup_projection();
    void setup();
    void draw();
};
