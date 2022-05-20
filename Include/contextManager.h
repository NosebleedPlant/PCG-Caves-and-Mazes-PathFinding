#pragma once
#include "map.h"

class ContextManager
{
private:
    const unsigned int INPUT_LIMIT = 2;
    unsigned int input_count = 0;
    GLFWwindow* window;
public:  
    //Creates a new context with given parameters
    GLFWwindow* makeContext(const unsigned int width,const unsigned int height)
    {
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
    int handleMouseClick(Map &map,glm::vec3 color)
    {
        int coord[]= {-1,-1};
        if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && input_count<INPUT_LIMIT) 
        {
            //getting cursor position
            double xpos,ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            if (map.setStartEnd(xpos/10,ypos/10,color)==1)
            {return 1;}
        }
        return 0;
    }
};