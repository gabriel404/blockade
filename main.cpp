#include "main.h"


int main()
{

	//window gl settings
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
	settings.antialiasingLevel = 2;
	
	//Window initialization and variables
	int wWidth = 800;
	int wHeight = 600;
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "OPENGL", sf::Style::Titlebar, settings);
	window.setPosition(sf::Vector2i(2200, 200));
	//end window initialization
	
	//initialize glew and check for errors
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	//end glew initializer
	
	//triangle vertices
	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,  // Top Right
		 0.5f, -0.5f, 0.0f,  // Bottom Right
		 -0.5f, -0.5f, 0.0f,  // Bottom Left
		 -0.5f,  0.5f, 0.0f   // Top Left 
	};

	/* GLfloat verticesz[] = { */
	/* 	 0.5f,  0.5f, 0.0f,  // Top Right */
	/* 	 0.0f, -0.5f, 0.0f,  // Bottom Right */
	/* 	 1.0f, -0.5f, 0.0f,  // Bottom Left */
	/* }; */
	//end triangle vertices
	GLuint indices[] = { //defines the order in which we are gonna draw the triangles
		0, 1, 3, //first triangle
		1, 2, 3 //second
	};

	//begins Vertex Array Object(VAO)
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //uses VAO as vertex array
	//init Vertex Buffer Object(VBO)
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind VBO to the Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copies the defined vertex to the buffer in memory(currently VBO)
    /* GL_STATIC_DRAW: the data will most likely not change at all or very rarely. */
    /* GL_DYNAMIC_DRAW: the data is likely to change a lot. */
    /* GL_STREAM_DRAW: the data will change every time it is drawn. */

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	
	//Element Buffer Object (EBO)
	GLuint EBO;
	glGenBuffers(1, &EBO); //set ebo buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); 
	glBindVertexArray(0); //unbind VAO
	

/* 	GLuint VAO1; */
/* 	glGenVertexArrays(1, &VAO1); */
/* 	glBindVertexArray(VAO1); */
/* 	GLuint VBO1; */
/* 	glGenBuffers(1, &VBO1); */
/* 	glBindBuffer(GL_ARRAY_BUFFER, VBO1); //bind VBO to the Buffer */
/* 	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesz), verticesz, GL_STATIC_DRAW); */ 
/* 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); */
/* 	glEnableVertexAttribArray(0); */ 
/* 	glBindVertexArray(0); //unbind VAO */


	//shaderProgram is the vertex and fragment shader compiled
	GLuint shaderProgram = LoadShader("vertexShader.vert", "fragmentShader.frag");
	/* GLuint shaderTemp = LoadShader("vertexShader.vert", "fragmentTemp.frag"); */

	//main game loop
	while(window.isOpen())
	{
		//event loop
		sf::Event evento;
		while(window.pollEvent(evento))
		{
			if (evento.type == sf::Event::KeyPressed)
				if(sf::Keyboard::Escape)
					window.close();
		}
		glViewport(0, 0, wWidth, wHeight);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); //bind VAO again
		/* glDrawArrays(GL_TRIANGLES, 0, 3); */
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); //common practice to unbind the VAO after using it (or so the tutorial says)

		/* glUseProgram(shaderTemp); */
		/* glBindVertexArray(VAO1); //bind VAO again */
		/* glDrawArrays(GL_TRIANGLES, 0, 3); */
		/* glBindVertexArray(0); */

		window.display();
	}
	//end main game loop
}
