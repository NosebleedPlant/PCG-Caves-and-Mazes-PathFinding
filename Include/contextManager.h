#pragma once
#include "GMap.h"

class ContextManager
{
private:
    unsigned int cell_dim;
    GLFWwindow* window;
public:  
    //Creates a new context with given parameters
    GLFWwindow* makeContext(const unsigned int width,const unsigned int height,unsigned int dim)
    {
        cell_dim = dim;
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // glfw window creation
        window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
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

    //Handle mouse click Coordinates
    bool handleMouseClick(GMap &map,glm::vec3 color)
    {
        int coord[]= {-1,-1};
        if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
        {
            double xpos,ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            if (map.setStartEnd(xpos/cell_dim,ypos/cell_dim,color)==true)
            {return true;}
        }
        return false;
    }
};