
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>

class bird {
public:
	float gravitySpeed = 0.01f;
	float vertices[20] = {
		// positions          // texture coords
		-0.4f,  0.10f, 0.0f,      1.0f, 1.0f,   // top right
		-0.4f, -0.10f, 0.0f,      1.0f, 0.0f,   // bottom right
		-0.60f, -0.10f, 0.0f,     0.0f, 0.0f,   // bottom left
		-0.60f,  0.10f, 0.0f,     0.0f, 1.0f    // top left 
	};
	unsigned int indices[6] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};
	unsigned int VAO, VBO, EBO;
	GLuint texture;
	bird();
	void gravity();
	void reinit();
	void del();
};