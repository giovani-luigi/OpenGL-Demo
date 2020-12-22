#include "Scene.h"
#include "SkyBoxSceneObject.h"

Scene::Scene(GLFWwindow* window) :
    m_window(window), m_camera(*this), m_lights(SceneLights::create_night(m_camera)),
    m_projection(), m_lastFrameTime(0), m_mouse_x(0), m_mouse_y(0), m_mouse_first(true),
    m_frame(0), m_enable_shadow(false)
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
        if (keyCode == GLFW_KEY_UP || keyCode == GLFW_KEY_W)
        {
            //if (!m_uniforms.collides(m_objects))
            m_camera.walk(Camera::FORWARD, step);
        }
        else if (keyCode == GLFW_KEY_DOWN || keyCode == GLFW_KEY_S)
        {
            m_camera.walk(Camera::BACKWARD, step);
        }
        else if (keyCode == GLFW_KEY_LEFT || keyCode == GLFW_KEY_A)
        {
            m_camera.walk(Camera::LEFT, step);
        }
        else if (keyCode == GLFW_KEY_RIGHT || keyCode == GLFW_KEY_D)
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
        
       // Debug::print_debug(m_camera, m_projection);
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
    m_camera.set_position(glm::vec3(0., 0.5, 0.0));

    // 4. create shaders to be used for the objects in the scene
    auto global_shader = create_global_shader();
    auto light_shader = create_light_shader();
        
    // 5. load and add objects
    
    // add ground
    m_objects.push_back(new FloorSceneObject(global_shader));

    // add skybox
    m_objects.push_back(new SkyBoxSceneObject(
    "Images\\skybox1\\",
    "LeftImage.png",
    "RightImage.png",
    "TopImage.png",
    "BottomImage.png",
    "FrontImage.png",
    "BackImage.png"
    ));
    
    // load statue from Wavefront file
    auto statue = FileSceneObject::LoadFromObjFile("milo.obj", global_shader, Material::create_default());
    statue->get_transformation().translate(0., 0., -2);
    statue->get_transformation().rotate_x_deg(-90);
    statue->get_transformation().scale(1.0f / 300, 1.0f / 300, 1.0f / 300);
    m_objects.push_back(statue);
    
    // load colums around the arch from Wavefront file
    auto column1 = FileSceneObject::LoadFromObjFile("Column.obj", global_shader, Material::create_dark_grey_rock());
    column1->get_transformation().translate(-0.8, 0., -1);
    column1->get_transformation().scale(1.0f / 3.5, 1.0f / 3.5, 1.0f / 3.5);
    m_objects.push_back(column1);
    auto column2 = FileSceneObject::LoadFromObjFile("Column.obj", global_shader, Material::create_dark_grey_rock());
    column2->get_transformation().translate(+0.8, 0., -1);
    column2->get_transformation().scale(1.0f / 3.5, 1.0f / 3.5, 1.0f / 3.5);
    m_objects.push_back(column2);

    // load entry arch from Wavefront file
    auto arch = FileSceneObject::LoadFromObjFile("Arch.obj", global_shader, Material::create_yellow_rock());
    arch->get_transformation().translate(0., 0., -1);
    arch->get_transformation().scale(1.0f / 3.5, 1.0f / 3.5, 1.0f / 3.5);
    m_objects.push_back(arch);

    // load entry arch from Wavefront file
    auto arch2 = FileSceneObject::LoadFromObjFile("Arch.obj", global_shader, Material::create_yellow_rock());
    arch2->get_transformation().translate(0., 0., -8);
    arch2->get_transformation().scale(1.0f / 3.5, 1.0f / 3.5, 1.0f / 3.5);
    m_objects.push_back(arch2);

    // load flashligth from Wavefront file
    auto flashlight = FileSceneObject::LoadFromObjFile("Linterna.obj", global_shader, Material::create_white_plastic());
    // hold the flashlight a bit lower than camera's eye and a bit to the front so it is within FOV
    flashlight->get_transformation().translate(0, -0.1, -0.2); // but if you hold too low, it goes out of the projection's FOV 
    flashlight->get_transformation().rotate_x_deg( -90 ); // fix model orientation
    flashlight->get_transformation().scale(1.0f / 100, 1.0f / 100, 1.0f / 100);
    flashlight->FollowsCamera = true;
    m_objects.push_back(flashlight);

}

void Scene::draw()
{
    m_frame++;

    double currentTime = glfwGetTime();
    m_deltaTime = currentTime - m_lastFrameTime;
    m_lastFrameTime = currentTime;
    
    // create the shadow map if enabled
    if (m_enable_shadow)
    {
        
    }

    // render all scene objects
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (SceneObject* obj : m_objects)
    {
        m_lights.set_uniforms(obj->get_shader()); // update light uniforms
        obj->draw(m_camera, m_projection, m_lights); // this will respect the polymorphism since we are using pointer
    }
}
