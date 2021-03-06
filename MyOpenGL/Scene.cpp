#include "Scene.h"
#include "SkyBoxSceneObject.h"

Scene::Scene(GLFWwindow* window) :
    m_window(window), m_camera(*this), m_lights(SceneLights::create_night(m_camera)),
    m_projection(), m_lastFrameTime(0), m_mouse_x(0), m_mouse_y(0), m_mouse_first(true),
    m_frame(0)
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
        m_frame++;

        double currentTime = glfwGetTime();
        m_deltaTime = currentTime - m_lastFrameTime;
        m_lastFrameTime = currentTime;

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

void Scene::process_mouse_button(int button, int action, int modifiers)
{
    if (action == GLFW_RELEASE)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            m_lights.toggle_flashlight();
        }
    }
}

void Scene::process_window_resize(int width, int height)
{
    // update projection's aspect ratio
    m_projection = create_projection();
}

glm::mat4 Scene::create_projection() const
{
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    return glm::perspective(MathUtils::deg_to_rad(67.0f), (float)width / height, PerspectiveZNear, PerspectiveZFar);
}

void Scene::setup()
{
    // 1. enable depth test
    glEnable(GL_DEPTH_TEST);

    // 2. disable cursor mode, so camera interaction works better
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 3. initialize shader parameters, such as camera and projections    
    m_projection = create_projection();
    m_camera.set_position(glm::vec3(0., 0.5, 0.0));

    // 4. create shaders to be used for the objects in the scene
    m_sceneShader = Shader("scene.vertex.shader", "scene.fragment.shader");

    // 5. load and add objects
    
    // add ground
    m_objects.push_back(new FloorSceneObject(m_sceneShader));

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
    auto statue = FileSceneObject::LoadFromObjFile("milo.obj", m_sceneShader, Material::create_default());
    statue->get_transformation().translate(0., 0., -3);
    statue->get_transformation().rotate_x_deg(-90);
    statue->get_transformation().scale(1.0f / 300, 1.0f / 300, 1.0f / 300);
    m_objects.push_back(statue);
    
    // load colums around the arch from Wavefront file
    auto column1 = FileSceneObject::LoadFromObjFile("Column.obj", m_sceneShader, Material::create_dark_grey_rock());
    auto column2 = new FileSceneObject(*column1); // creates a copy
    auto column3 = new FileSceneObject(*column1); // creates a copy
    auto column4 = new FileSceneObject(*column1); // creates a copy
    column1->get_transformation().translate(-0.8, 0., -1);
    column1->get_transformation().scale(1.0f / 3.5, 1.0f / 3.5, 1.0f / 3.5);
    column2->get_transformation().translate(+0.8, 0., -1);
    column2->get_transformation().scale(1.0f / 3.5, 1.0f / 3.5, 1.0f / 3.5);
    column3->get_transformation().translate(-0.8, 0., -4.0f);
    column3->get_transformation().scale(1.0f / 3.5, 1.0f / 3.5, 1.0f / 3.5);
    column4->get_transformation().translate(+0.8, 0., -4.0f);
    column4->get_transformation().scale(1.0f / 3.5, 1.0f / 3.5, 1.0f / 3.5);
    m_objects.push_back(column1);
    m_objects.push_back(column2);
    m_objects.push_back(column3);
    m_objects.push_back(column4);

    // load colums from Wavefront file
    auto columnAlt1 = FileSceneObject::LoadFromObjFile("Column2.obj", m_sceneShader, Material::create_yellow_rock());
    auto columnAlt2 = new FileSceneObject(*columnAlt1); // creates a copy
    auto columnAlt3 = new FileSceneObject(*columnAlt1); // creates a copy
    auto columnAlt4 = new FileSceneObject(*columnAlt1); // creates a copy
    columnAlt1->get_transformation().translate(-0.8, 0., -2.0f);
    columnAlt1->get_transformation().scale(1.0f / 5.5, 1.0f / 5.5, 1.0f / 5.5);
    columnAlt2->get_transformation().translate(+0.8, 0., -2.0f);
    columnAlt2->get_transformation().scale(1.0f / 5.5, 1.0f / 5.5, 1.0f / 5.5);
    columnAlt3->get_transformation().translate(-0.8, 0., -3.0f);
    columnAlt3->get_transformation().scale(1.0f / 5.5, 1.0f / 5.5, 1.0f / 5.5);
    columnAlt4->get_transformation().translate(+0.8, 0., -3.0f);
    columnAlt4->get_transformation().scale(1.0f / 5.5, 1.0f / 5.5, 1.0f / 5.5);
    m_objects.push_back(columnAlt1);
    m_objects.push_back(columnAlt2);
    m_objects.push_back(columnAlt3);
    m_objects.push_back(columnAlt4);

    // load front and back arch from Wavefront file
    auto arch1 = FileSceneObject::LoadFromObjFile("Arch.obj", m_sceneShader, Material::create_yellow_rock());
    auto arch2 = new FileSceneObject(*arch1); // copy ctor
    arch1->get_transformation().translate(0., 0., -1.0f);
    arch1->get_transformation().scale(1.0f / 3.5, 1.0f / 3.5, 1.0f / 3.5);
    arch2->get_transformation().translate(0., 0., -4.0f);
    arch2->get_transformation().scale(1.0f / 3.5, 1.0f / 3.5, 1.0f / 3.5);
    m_objects.push_back(arch1);
    m_objects.push_back(arch2);

    // load flashligth from Wavefront file
    auto flashlight = FileSceneObject::LoadFromObjFile("Linterna.obj", m_sceneShader, Material::create_white_plastic());
    // hold the flashlight a bit lower than camera's eye and a bit to the front so it is within FOV
    flashlight->get_transformation().translate(0, -0.1, -0.2); // but if you hold too low, it goes out of the projection's FOV 
    flashlight->get_transformation().rotate_x_deg( -90 ); // fix model orientation
    flashlight->get_transformation().scale(1.0f / 100, 1.0f / 100, 1.0f / 100);
    flashlight->FollowsCamera = true;
    m_objects.push_back(flashlight);

}

void Scene::draw()
{
    // update viewport size
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

    // render all scene objects
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (SceneObject* obj : m_objects)
    {
        // these calls will respect the polymorphism since we are using pointer
        obj->configure(m_camera, m_projection, m_lights);
        obj->draw(); 
    }
}
