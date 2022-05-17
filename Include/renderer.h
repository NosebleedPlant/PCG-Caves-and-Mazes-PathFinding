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
            throw("Failed to create GLFW window");
            throw(-1);
        }
        glfwMakeContextCurrent(window); 

        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw("Failed to initialize GLAD\n");
            throw(-2);
        }
        return window;
    }

    //Clears screen
    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    //Draw Triangles Command
    void draw(const VertexArray& vao,const ElementBuffer& ebo,const Shader& shader) const
    {
        vao.bind();
        glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0);
    }

};