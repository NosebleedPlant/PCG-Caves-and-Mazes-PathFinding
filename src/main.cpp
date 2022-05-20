//STD
#include <iostream>
#include <string.h>
//OGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//Custom
#include "shader.h"
#include "elementBuffer.h"
#include "vertexArray.h"
#include "contextManager.h"
#include "map.h"
#include "pathFinder.h"

//SETTING CONSTANTS:
const unsigned int SCR_WIDTH = 910;
const unsigned int SCR_HEIGHT = 910;
const unsigned int GRID_WIDTH = SCR_WIDTH/10;
const unsigned int GRID_HEIGHT = SCR_HEIGHT/10;
const glm::vec3 DEAD_COLOR = glm::vec3(0.2f, 0.3f, 0.3f);		//green
const glm::vec3 ALIVE_COLOR = glm::vec3(1.0f, 0.5f, 0.2f);		//orange
const glm::vec3 SELECTION_COLOR = glm::vec3(1.0f, 1.0f, 0.0f);	//yellow
const glm::mat4 projection = glm::ortho(0.0f, float(SCR_WIDTH), float(SCR_HEIGHT), 000.0f, -1.0f, 1.0f);//projection matrix
//Verticies for Gird Cell
const float vertices[] = {
	// positions
	10.0f,  10.0f, 0.0f,   // top right
	10.0f,  0.0f, 0.0f,    // bottom right
	0.0f,  0.0f, 0.0f,     // bottom left
	0.0f,  10.0f, 0.0f,    // top left 
};
const unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

//MAIN LOOP:
int main(int argc,char* argv[])
{
	//SECTION 1: CHECK RUNTIME FLAGS
	std::string flag;
	if(argc <2)
	{
		std::cout << "Please specify flag" << std::endl;
		std::cout << "-Caves: generates caves" << std::endl;
		std::cout << "-Maze: generates maze" << std::endl;
		return -1;
	}
	else
	{flag = std::string(argv[1]);}
	
	//SECTION 2: OPENGL SETUP
    ContextManager contextManager;
    GLFWwindow *window;
	try
	{
		window = contextManager.makeContext(SCR_WIDTH, SCR_HEIGHT);
	}
	catch(int e)
	{
		if (e==-1){std::cout << "Failed to create GLFW window" << std::endl;glfwTerminate();return -1;}
		else if (e==-2){std::cout << "Failed to initialize GLAD" << std::endl;glfwTerminate();return -1;}
	}

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
	shader.setMat4("projection", projection);

	//SECTION 3: CAVE GENERATION
	Map map(GRID_WIDTH,GRID_HEIGHT,DEAD_COLOR, ALIVE_COLOR);
	if(flag=="-Maze")
	{
		std::cout<<"Under Construction"<< std::endl;
		return -1;
	}
	else if(flag=="-Caves")
	{map.generateCaves(4,4,4,40);}

	//SECTION 4: PATH FINDING
	PathFinder pathFinder;

    // SECTION 4: VISUALIZATION
	int frame_count = 0;
	glm::mat4 translation;//translation matrix initialization for redering grid cells
	while (!glfwWindowShouldClose(window))
	{		
		// render
		glClear(GL_COLOR_BUFFER_BIT);
		vao.bind();
		
		//prints map
		for (size_t y = 0; y < GRID_HEIGHT; y++)
		{
			for (size_t x = 0; x < GRID_WIDTH; x++)
			{
				translation = glm::translate(glm::mat4(1), glm::vec3(10.0f*x, 10.0f*y, 0.0f));//set transform of cell
				shader.setMat4("translation", translation);
				shader.setVec3("color", map.getCell(x,y));//set color
				glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0);
			}
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwWaitEvents();
		if(contextManager.handleMouseClick(map,SELECTION_COLOR) == 1)
			pathFinder.flood_fill(map);

	}
	// glfw: terminate, clearing all previously allocated GLFWresources.
	glfwTerminate();
	return 0;
}