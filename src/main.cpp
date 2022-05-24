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
#include "GMap.h"
#include "pathFinder.h"

//SETTING CONSTANTS:
const unsigned int SCR_DIM = 910;
const unsigned int CELL_DIM = 10;
const unsigned int GRID_DIM = SCR_DIM/CELL_DIM;
const glm::vec3 DEAD_COLOR = glm::vec3(0.04f, 0.15f, 0.21f);		//deep blue #0a2635
const glm::vec3 ALIVE_COLOR = glm::vec3(0.09f, 0.41f, 0.25f);		//green #166841
const glm::vec3 SELECTION_COLOR = glm::vec3(0.90f, 0.87f, 0.81f);	//off-white #F2EFE9
const glm::vec3 FLOOD_COLOR = glm::vec3(0.96f, 0.38f, 0.22f);		//orange #f56038
const glm::vec3 AS_OPENED_COLOR = glm::vec3(1.00f, 0.79f, 0.48f);	//pale yellow #ffca7a
const glm::vec3 AS_CLOSED_COLOR = glm::vec3(0.97f, 0.64f, 0.15f);	//orange yellow #f7a325
const glm::vec3 AS_OPTIMAL_COLOR = glm::vec3(0.57f, 0.91f, 0.90f);	//teal #92e7e5
const glm::mat4 projection = glm::ortho(0.0f, float(SCR_DIM), float(SCR_DIM), 000.0f, -1.0f, 1.0f);//projection matrix
//Verticies for Gird Cell
const float vertices[] = {
	// positions
	float(CELL_DIM),  	float(CELL_DIM), 	0.0f,   // top right
	float(CELL_DIM),  	0.0f, 				0.0f,    // bottom right
	0.0f,  				0.0f, 				0.0f,     // bottom left
	0.0f,  				float(CELL_DIM), 	0.0f,    // top left 
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
		window = contextManager.makeContext(SCR_DIM, SCR_DIM,CELL_DIM);
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
	GMap map(GRID_DIM,DEAD_COLOR, ALIVE_COLOR);
	if(flag=="-Maze")
	{
		std::cout<<"Under Construction"<< std::endl;
		glfwTerminate();
		return -1;
	}
	else if(flag=="-Caves")
	{map.generateCaves(4,4,4,50);}
	else
	{
		glfwTerminate();
		return -1;
	}

	//SECTION 4: PATH FINDING
	PathFinder pathFinder(AS_OPENED_COLOR,AS_CLOSED_COLOR,AS_OPTIMAL_COLOR);

    // SECTION 4: VISUALIZATION
	int frame_count = 0;
	glm::mat4 translation;//translation matrix initialization for redering grid cells

	while (!glfwWindowShouldClose(window))
	{		
		// render
		glClear(GL_COLOR_BUFFER_BIT);
		vao.bind();
		
		//prints map
		for (size_t y = 0; y < GRID_DIM; y++)
		{
			for (size_t x = 0; x < GRID_DIM; x++)
			{
				translation = glm::translate(glm::mat4(1), glm::vec3(float(CELL_DIM)*x, float(CELL_DIM)*y, 0.0f));//set transform of cell
				shader.setMat4("translation", translation);
				shader.setVec3("color", map.getCell(x,y));//set color
				glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0);
			}
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwWaitEvents();
		
		//Check for start_end input
		if(contextManager.handleMouseClick(map,SELECTION_COLOR) == true)
		{
			//if start_end provided, conduct pathing
			if(pathFinder.flood_fill(map,FLOOD_COLOR)==true)
			{
				pathFinder.aStar(map);
			}
			map.setStartEndCells(SELECTION_COLOR);
		}
	}
	// glfw: terminate, clearing all previously allocated GLFWresources.
	glfwTerminate();
	return 0;
}