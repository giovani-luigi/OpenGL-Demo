#include "Scene.h"

Scene::Scene(GLFWwindow* window) :
    m_window(window), m_lastFrameTime(0), m_frame(0),
    m_mouse_first(true), m_camera(*this), m_projection()
{
}

Scene::~Scene()
{
    for (const SceneObject* object : m_objects)
    {
        delete(object);
    }
}

void Scene::run()
{
    // setup the scene
    setup();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_window))
    {
        draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}


void Scene::process_key(int keyCode, int scanCode, int action, int modifiers)
{
    if (action == GLFW_REPEAT || action == GLFW_PRESS)
    {
        //auto cam_pos = m_uniforms.camera.get_position();

        const float step = m_deltaTime * m_keyboard_speed;
        if (keyCode == GLFW_KEY_UP)
        {
            //if (!m_uniforms.collides(m_objects))
            m_camera.walk(Camera::FORWARD, step);
        }
        else if (keyCode == GLFW_KEY_DOWN)
        {
            m_camera.walk(Camera::BACKWARD, step);
        }
        else if (keyCode == GLFW_KEY_LEFT)
        {
            m_camera.walk(Camera::LEFT, step);
        }
        else if (keyCode == GLFW_KEY_RIGHT)
        {
            m_camera.walk(Camera::RIGHT, step);
        }
        else if (keyCode == GLFW_KEY_PAGE_UP)
        {
            m_camera.move(Camera::UP, step);
        }
        else if (keyCode == GLFW_KEY_PAGE_DOWN)
        {
            m_camera.move(Camera::DOWN, step);
        }
        else if (keyCode == GLFW_KEY_KP_ADD)
        {
            m_camera.zoom(0.25);
        }
        else if (keyCode == GLFW_KEY_KP_SUBTRACT)
        {
            m_camera.zoom(-0.25);
        }
        else if (keyCode == GLFW_KEY_S)
        {
        }
        Debug::print_debug(m_camera, m_projection);
    }
}

void Scene::process_cursor(float xpos, float ypos)
{
    if (m_mouse_first)
    {
        m_mouse_x = xpos;
        m_mouse_y = ypos;
        m_mouse_first = false;
    }

    auto deltaX = xpos - m_mouse_x;
    auto deltaY = ypos - m_mouse_y;

    m_mouse_x = xpos;
    m_mouse_y = ypos;

    m_camera.yaw(deltaX * m_mouse_sensitivity);
    m_camera.pitch(deltaY * m_mouse_sensitivity * -1);
}

void Scene::process_viewport_resize(int width, int height)
{
    // update projection's aspect ratio
    setup_projection();
}

Shader Scene::create_global_shader()
{
    return Shader("default.vertex.shader", "global.fragment.shader");
}

Shader Scene::create_light_shader()
{
    return Shader("default.vertex.shader", "light.fragment.shader");
}

void Scene::setup_projection()
{
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    m_projection = glm::perspective(MathUtils::deg_to_rad(67.0f), (float)width / height, 0.1f, 10.0f);
}

void Scene::setup()
{
    // 1. enable depth test
    glEnable(GL_DEPTH_TEST);

    // 2. disable cursor mode, so camera interaction works better
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 3. initialize shader parameters, such as camera and projections    
    setup_projection();
    m_camera.set_position(glm::vec3(0., 0.5, 1.0));

    // 4. create shaders to be used for the objects in the scene
    auto global_shader = create_global_shader();
    auto light_shader = create_light_shader();
        
    // 5. load and add objects

    // add ground
    m_objects.push_back(new FloorSceneObject(global_shader));

    /*
    // add walls by distorting the cube
    auto cube = new CubeSceneObject(global_shader);
    cube->get_transformation().translate(0.0f, 0.5f, 0.0f);
    cube->get_transformation().scale(0.1, 0.1, 0.1);
    m_objects.push_back(cube);
    */
    // load statue from Wavefront file

    auto statue = FileSceneObject::LoadFromObjFile("statue.obj", global_shader, Material::create_white_marble());
    statue->get_transformation().scale(1.0f / 200, 1.0f / 200, 1.0f / 200);
    m_objects.push_back(statue);
}

void Scene::draw()
{
    m_frame++;

    double currentTime = glfwGetTime();
    m_deltaTime = currentTime - m_lastFrameTime;
    m_lastFrameTime = currentTime;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render all scene objects
    for (SceneObject* obj : m_objects)
    {
        obj->draw(m_camera, m_projection); // this will respect the polymorphism since we are using pointer
    }
}
