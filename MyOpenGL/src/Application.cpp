#include <iostream>
#include <GL/glew.h>    // erro aqui? selecionar "x86" ao invés de "x64" ao lado de "Play"
#include <GLFW/glfw3.h> 
#include <filesystem>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc

#include "../Scene.h" 

Scene * g_scene;

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  
 *   Aluno: Giovani Luigi
 *
 *   -------------
 *   Professor!!!!
 *   -------------
 *
 *   Antes de compilar, certifique-se que a opção "x86"
 *   (ao lado do botão "Play" da IDE) está selecionada ao invés de x64!
 *
 *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void onWindowResize(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
    g_scene->process_viewport_resize(width, height);
}

void onCursorPosition(GLFWwindow* window, double xpos, double ypos)
{
    g_scene->process_cursor(xpos, ypos);
}

void onKeyInput(GLFWwindow* window, int keyCode, int scanCode, int action, int modifiers)
{
    if (g_scene == nullptr) return; // scene not initialized yet
    // forward call to instance
    g_scene->process_key(keyCode, scanCode, action, modifiers);	
}

void onMouseButton(GLFWwindow* window, int button, int action, int modifiers)
{
    if (g_scene == nullptr) return; // scene not initialized yet
    g_scene->process_mouse_button(button, action, modifiers);
}

// initialize all libraries and setup the window object
GLFWwindow * setupWindow() {

	/* Initialize the library */
    if (!glfwInit())
        return nullptr;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow * window = glfwCreateWindow(800, 800, "OpenGL - Giovani Luigi - 2020", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    glfwSetWindowSizeCallback(window, onWindowResize);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
	
    glfwSetKeyCallback(window, onKeyInput);
    glfwSetCursorPosCallback(window, onCursorPosition);
    glfwSetMouseButtonCallback(window, onMouseButton);
	
    /* After creating context, initialize GLEW */
    if (glewInit() != GLEW_OK) {
        std::cout << "Error. Cannot initialize GLEW" << std::endl;
    }

    std::cout << "Working dir is " << std::filesystem::current_path() << '\n';
	
    // print driver data
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Card driver: " << glGetString(GL_RENDERER) << std::endl;
	
    return window;	
}


int main(void) {

	auto window = setupWindow();

    g_scene = new Scene(window);
    g_scene->run();
	
    glfwTerminate();
    return 0;
}