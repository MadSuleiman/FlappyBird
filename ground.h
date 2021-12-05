#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>

class ground {
public:
	float vertices[20] = {
		// positions        // texture coords
		1.0f,  -0.70f, 0.0f,    1.0f, 1.0f,   // top right
		1.0f, -1.0f, 0.0f,      1.0f, 0.0f,   // bottom right
		-1.0f, -1.0f, 0.0f,     0.0f, 0.0f,   // bottom left
		-1.0f,  -0.7f, 0.0f,    0.0f, 1.0f    // top left  
	};

	unsigned int indices[6] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};
	unsigned int VAO, VBO, EBO;
	GLuint texture;
	ground();
	void reinit();
	void del();
};
