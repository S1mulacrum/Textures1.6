#include <string>
#include <fstream>
#include <sstream>
#include "ShaderProg.h"

ShaderProg::ShaderProg(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    std::string vertexShaderStr;
    std::string fragmentShaderStr;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

 // Удостоверимся, что ifstream объекты могут выкидывать исключения
    //Make sure that ifstream objects can pop out the exceptions
    vertexShaderFile.exceptions(std::ifstream::failbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit);
    try
    {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        //записываем содержимое шейдеров в потоковый буффер
        vShaderStream << vertexShaderFile.rdbuf();//write down vertex shader's content in stream buffer
        fShaderStream << fragmentShaderFile.rdbuf();//write down fragment shader's content in stream buffer

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexShaderStr = vShaderStream.str();
        fragmentShaderStr = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        printf("ERROR: Shader file couldn't be successfully read\n");
    }

    //Получаем коды для наших шейдеров
    //Get pointers to shaders code
    const GLchar* vertexShaderCode = vertexShaderStr.c_str();
    const GLchar* fragmentShaderCode = fragmentShaderStr.c_str();
    //Creating the shaders
    GLuint vertexShader, fragmentShader;
    GLint success;
    GLchar infoLog[512];
    
///Vertex shader compilation
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Vertex Shader compilation failed with error: %s\n", infoLog);
    }

///Fragment shader compilation
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Fragment Shader compilation failed with error: %s\n", infoLog);
    }

    shaderProgram_sp = glCreateProgram();
    glAttachShader(shaderProgram_sp, vertexShader);
    glAttachShader(shaderProgram_sp, fragmentShader);
    glLinkProgram(shaderProgram_sp);

    glGetProgramiv(shaderProgram_sp, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram_sp, 512, NULL, infoLog);
        printf("Error with shader program creatng %s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint ShaderProg::getProgramDesc()
{
    return shaderProgram_sp;
}

void ShaderProg::Use()
{
    glUseProgram(shaderProgram_sp);
}
