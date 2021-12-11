#include<iostream>
#include"Libraries/include/glad/glad.h"
#include"Libraries/include/GLFW/glfw3.h"
#include"Libraries/include/SOIL2/SOIL2.h"
#include<random>

class pipes {
public:
	float spot;
	float speed = 0.0002f;
	bool pointAdd = false;
	float vertices[20] = {
		// positions          // colors           // texture coords
		1.25f,  1.3f, 0.0f,      1.0f, 1.0f,   // top right
		1.25f, -1.0f, 0.0f,     1.0f, 0.0f,   // bottom right
		1.0f, -1.0f, 0.0f,    0.0f, 0.0f,   // bottom left
		1.0f,  1.3f, 0.0f,     0.0f, 1.0f    // top left  
	};
	unsigned int indices[6] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};
	unsigned int VAO, VBO, EBO;
	GLuint texture;
	pipes(float t1);
	void reinit();
	void del();
};

pipes::pipes(float t1) {
	vertices[0] = vertices[0] + t1;
	vertices[5] = vertices[5] + t1;
	vertices[10] = vertices[10] + t1;
	vertices[15] = vertices[15] + t1;
	
	texture = SOIL_load_OGL_texture
	(
		"pipes.png",
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

void pipes::reinit() {
	
	if (vertices[0] > -1.0f) {
		vertices[0] = vertices[0] - speed;
		vertices[5] = vertices[5] - speed;
		vertices[10] = vertices[10] - speed;
		vertices[15] = vertices[15] - speed;


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
	else {
		pointAdd = false;
		vertices[0] = 1.25f;
		vertices[5] = 1.25f;
		vertices[10] = 1.0f;
		vertices[15] = 1.0f;
		float temp = rand() % 60;
		temp -= 30;
		temp /= 100;
		vertices[1]  = 1.3f;
		vertices[6] = -1.0f;
		vertices[11] = -1.0f;
		vertices[16] = 1.3f;

		vertices[1] += temp;
		vertices[6] += temp;
		vertices[11] += temp;
		vertices[16] += temp;

	}
};
void pipes::del() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}