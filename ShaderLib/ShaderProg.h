#pragma once
//#include <glew.h>
#include <GLEW/glew.h>

class ShaderProg
{
public:
    ShaderProg(const GLchar* vertexPath, const GLchar* fragmentPath);
    GLuint getProgramDesc();
    void Use();

    GLuint shaderProgram_sp;
};

