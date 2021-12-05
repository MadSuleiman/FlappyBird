#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>

class ground {
public:
	unsigned int VAO, VBO, EBO;
	GLuint texture;
	ground();
	void del();
};
