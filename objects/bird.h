#include<iostream>
#include"../Libraries/include/glad/glad.h"
#include"../Libraries/include/GLFW/glfw3.h"
#include"../Libraries/include/SOIL2/SOIL2.h"
// #include<SOIL/SOIL.h>

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
	float gravity = 0.000f;
	void reinit(float gravitySpeed);
	void del();
};

bird::bird() {
	
	texture = SOIL_load_OGL_texture
	(
		"./textures/bird.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
void bird::reinit(float gravity) {
	
	if (vertices[6] - gravity > -0.7f && vertices[1] - gravity < 1.0f) {
		vertices[1] = vertices[1] - gravity;
		vertices[6] = vertices[6] - gravity;
		vertices[11] = vertices[11] - gravity;
		vertices[16] = vertices[16] - gravity;

		glBindVertexArray(0);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
};

 void bird::del() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}