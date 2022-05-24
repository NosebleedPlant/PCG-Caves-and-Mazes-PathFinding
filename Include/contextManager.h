#pragma once
#include "GMap.h"
/*
Author: Yalmaz
This class manages the OPENGL context by creating and checking input etc
*/
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
            glfwGetCursorPos(window, &xpos, &ypos);//get cursor position
            if((xpos/cell_dim)>=map.DIM || (ypos/cell_dim)>=map.DIM ||
               (xpos/cell_dim)<0 || (ypos/cell_dim)<0)//confirm if in bounds
            {return false;}
            
            else if (map.setStartEnd(floor(xpos/cell_dim),floor(ypos/cell_dim),color)==true)//check if path finding succedded
            {return true;}
        }
        return false;
    }
};