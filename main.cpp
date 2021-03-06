#include <iostream>

//OpenGL
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//file loaders
#include "loaders/shader.h"
#include "loaders/bmploader.h"
#include "loaders/stb_image.h"
#include "texture.h"

//key handler
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	//initialize GLFW
	if(glfwInit())
	{
		std::cout << "GLFW Initialized" << std::endl;
	}else
	{
		std::cout << "GLFW error, not initizlized" << std::endl;
		return -1;
	}

	// Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create window and checks for errors
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Engine", nullptr, nullptr); 
	if(!window)
	{
		std::cout << "Window could not be loaded" << std::endl;
		glfwTerminate();
		return -1;
	}
	//make the window context current
	glfwMakeContextCurrent(window);
	//end window initialization
	
	//initialize glew and check for errors
	glewExperimental = GL_TRUE;
	if(glewInit() == GLEW_OK)
	{
		std::cout << "GLEW Initialized" << std::endl;
	}else{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	//end glew initializer

	int w_Width, w_Height;
	glfwGetFramebufferSize(window, &w_Width, &w_Height);
	glViewport(0, 0, w_Width, w_Height);
	
	//shaderProgram is the vertex and fragment shader compiled
	GLuint shaderProgram = LoadShader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
	
    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
    };

	//end triangle vertices
	GLuint indices[] = { //defines the order in which we are gonna draw the triangles
		0, 1, 3, //first triangle
		1, 2, 3 //second 
	};

	//load texture
	
	//VBO = Vertex Buffer Object
	//VAO = Vertex Array Object
	//EBO = Element Buffer Object
	GLuint VBO, VAO, EBO;
	//number of attributes spaces to use
	GLint attrN = 8;

	//Generates Objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); //set ebo buffers

	//Bind VAO first, then bind and set vertex buffer(s) and attribute pointer(s)
	glBindVertexArray(VAO); //uses VAO as vertex array

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind VBO to the Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copies the defined vertex to the buffer in memory(currently VBO)
    /* GL_STATIC_DRAW: the data will most likely not change at all or very rarely. */
    /* GL_DYNAMIC_DRAW: the data is likely to change a lot. */
    /* GL_STREAM_DRAW: the data will change every time it is drawn. */

	//Element Buffer Object (EBO)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attrN * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0); 

	//Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attrN * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Texture Attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, attrN * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	unsigned int texture1, texture2;

	LoadTexture(texture1, "resources/wall.jpg", "JPG");
	LoadTexture(texture2, "resources/seta.png", "PNG");

	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);


	//main game loop
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glfwSetKeyCallback(window, key_callback); //key events
	
		//Render
		//Clear Color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Change color with time
		/* double time = glfwGetTime(); */
		/* GLfloat timeValue = time; */
		/* GLfloat greenValue = (std::sin(timeValue) / 2) + 0.5; */
		/* GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); */
		/* glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); */

		/* glUniform1f(glGetUniformLocation(shaderProgram, "aloha"), 0.4f); */

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO); //bind VAO again
		/* glDrawArrays(GL_TRIANGLES, 0, 3); */
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); //common practice to unbind the VAO after using it (or so the tutorial says)

		glfwSwapBuffers(window);
	}
	//end main game loop
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}
