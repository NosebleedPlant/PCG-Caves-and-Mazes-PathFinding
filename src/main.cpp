//STD
#include <iostream>
#include <array>
#include <random>
//OGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
//Custom
#include "shader.h"
#include "elementBuffer.h"
#include "vertexArray.h"
#include "renderer.h"

const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 900;

int main()
{
    Renderer renderer;
    GLFWwindow *window;
	try
	{
		window = renderer.makeContext(SCR_WIDTH, SCR_HEIGHT);
	}
	catch(int e)
	{
		if (e==-1){std::cout << "Failed to create GLFW window" << std::endl;glfwTerminate();return -1;}
		if (e==-2){std::cout << "Failed to initialize GLAD" << std::endl;glfwTerminate();return -1;}
	}

    //set vertices (abstract later?)
    float vertices[] = {
        // positions          // texture coords
        10.0f,  10.0f, 0.0f,   // top right
        10.0f,  0.0f, 0.0f,   // bottom right
        0.0f,  0.0f, 0.0f,   // bottom left
        0.0f,  10.0f, 0.0f,   // top left 
    };
	unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    //Build and Bind shaders
    Shader shader("./Include/shaderVertex.vs","./Include/shaderFragment.fs");
    shader.use();

    //Make buffer objects
	VertexArray vao;
	VertexBuffer vbo(vertices,sizeof(vertices));
	ElementBuffer ebo(indices,sizeof(indices));
    
	//Setup layout
    VertexBufferLayout layout;
	layout.push(3);
	vao.addVertexBuffer(vbo,layout);

    //setup projection
	glm::mat4 projection    = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, 900.0f, 900.0f, 000.0f, -1.0f, 1.0f);
	shader.setMat4("projection", projection);
	///test
	shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.2f, 1.0f));
	glm::mat4 translation;

    // render loop
	int i=0;
	while (!glfwWindowShouldClose(window))
	{		
		// render
		glClear(GL_COLOR_BUFFER_BIT);
		vao.bind();
		
		//prints map
		for (size_t y = 0; y < 90; y++)
		{
			for (size_t x = 0; x < 90; x++)
			{
				translation = glm::translate(glm::mat4(1), glm::vec3(10.0f*x, 10.0f*y, 0.0f));
				shader.setMat4("translation", translation);
				glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0);
			}
		}
		

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
		i++;
	}
	// glfw: terminate, clearing all previously allocated GLFWresources.
	glfwTerminate();
	return 0;
}