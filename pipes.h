#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>

class pipes {
public:
	float spot;
	float speed = 0.0005f;
	unsigned int VAO, VBO, EBO;
	GLuint texture;
	pipes(float t1);
	void reinit();
	void del();
};