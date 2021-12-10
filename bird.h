#include<iostream>
#include"Libraries/include/glad/glad.h"
#include"Libraries/include/GLFW/glfw3.h"
#include"Libraries/include/SOIL2/SOIL2.h"

class bird {
public:
	float vertices[20] = {
		// positions          // texture coords
		-0.43f,  0.07f, 0.0f,      1.0f, 1.0f,   // top right
		-0.43f, -0.07f, 0.0f,      1.0f, 0.0f,   // bottom right
		-0.57f, -0.07f, 0.0f,     0.0f, 0.0f,   // bottom left
		-0.57f,  0.07f, 0.0f,     0.0f, 1.0f    // top left 
	};
	unsigned int indices[6] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};
	unsigned int VAO, VBO, EBO;
	GLuint texture;
	bird();
	float gravity = 0.001f;
	void reinit(float gravitySpeed);
	void del();
};