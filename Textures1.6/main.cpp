#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderProg.h"
//#include <Soil/SOIL.h>

GLuint Width = 700;
GLuint Height = 500;

int main(int argc, char** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(Width, Height, "Textures", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    glewInit();

    glViewport(0, 0, Width, Height);
    ShaderProg shaderProg("Shaders/vertexShader.gs", "Shaders/fragmentShader.gs");

    return 0;
}