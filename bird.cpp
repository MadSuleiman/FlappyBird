#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>
#include"bird.h"

bird::bird() {

	texture = SOIL_load_OGL_texture
	(
		"bird.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
void bird::reinit() {
}
void bird::gravity() {
	vertices[1] = vertices[1] - gravitySpeed;
	vertices[9] = vertices[9] - gravitySpeed;
	vertices[17] = vertices[17] - gravitySpeed;
	vertices[25] = vertices[25] - gravitySpeed;
}
 void bird::del() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}