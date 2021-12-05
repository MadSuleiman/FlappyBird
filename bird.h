#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>

class bird {
public:
	unsigned int VAO, VBO, EBO;
	GLuint texture;
	bird();
	float gravity = 0.1f;
	void reinit(float gravitySpeed);
	void del();
};