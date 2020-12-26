#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLM/ext/matrix_clip_space.hpp"
#include <vector>
#include <filesystem>

#include "Debug.h"
#include "SceneObject.h"
#include "Shader.h"
#include "Camera.h"
#include "CubeSceneObject.h"
#include "FileSceneObject.h"
#include "FloorSceneObject.h"

class Scene
{
public:

    Scene(GLFWwindow* window);
    ~Scene();

    void run();
    void process_key(int keyCode, int scanCode, int action, int modifiers);
    void process_cursor(float xpos, float ypos);
    void process_mouse_button(int button, int action, int modifiers);
    void process_window_resize(int width, int height);

    float PerspectiveZNear = 0.1f;
    float PerspectiveZFar = 10.0f;

private:

    Shader m_sceneShader;
    GLFWwindow* m_window;
    std::vector<SceneObject*> m_objects; // it uses pointers due to polypmorphic behavior, which results in 'object slicing'
    Camera m_camera;
    SceneLights m_lights;
    glm::mat4 m_projection;
    double m_lastFrameTime;
    double m_deltaTime = 0;
    float m_mouse_x;
    float m_mouse_y;
    bool m_mouse_first;
    int m_frame;
    float m_mouse_sensitivity = 0.1f;
    float m_keyboard_speed = 2.5f;
    
    glm::mat4 create_projection() const;

    void setup();
    void draw();
};
