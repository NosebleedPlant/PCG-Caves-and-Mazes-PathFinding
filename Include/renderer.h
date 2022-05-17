#pragma once
#include <glad/glad.h>
#include "shader.h"
#include "vertexArray.h"
#include "elementBuffer.h"

struct Renderer
{
    //Creates a new context with given parameters
    GLFWwindow* makeContext(const unsigned int width,const unsigned int height)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // glfw window creation
        GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            glfwTerminate();
            throw(-1);
        }
        glfwMakeContextCurrent(window); 

        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw(-2);
        }
        return window;
    }
};