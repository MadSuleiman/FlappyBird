#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>
#include"shaderClass.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void displayFunc(GLuint textureBird, GLuint textureFloor, GLuint texturePipes, unsigned int VAO, unsigned int VAOFloor, unsigned int VAOPipes) {
	// bind bird Texture
	glBindTexture(GL_TEXTURE_2D, textureBird);

	// render container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// bind floor Texture
	glBindTexture(GL_TEXTURE_2D, textureFloor);

	// render container
	glBindVertexArray(VAOFloor);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// bind floor Texture
	glBindTexture(GL_TEXTURE_2D, texturePipes);

	// render container
	glBindVertexArray(VAOPipes);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void moveObjects() {

}
int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(1200, 900, "FlappyBird", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create window.";
		glfwTerminate();
		return -1;
	}

	//Make context this window and allow resizing
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

    // build and compile our shader program
	Shader ourShader("default.vert", "default.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		// positions          // colors           // texture coords
		-0.4f,  0.10f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		-0.4f, -0.10f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.60f, -0.10f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.60f,  0.10f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	unsigned int indices[] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	float verticesFloor[] = {     
		// positions          // colors           // texture coords
		1.0f,  -0.70f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-1.0f,  -0.7f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left  
	};
	unsigned int indicesFloor[] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};

	unsigned int VBOFloor, VAOFloor, EBOFloor;
	glGenVertexArrays(1, &VAOFloor);
	glGenBuffers(1, &VBOFloor);
	glGenBuffers(1, &EBOFloor);

	glBindVertexArray(VAOFloor);

	glBindBuffer(GL_ARRAY_BUFFER, VBOFloor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFloor), verticesFloor, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOFloor);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesFloor), indicesFloor, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	float verticesPipes[] = {
		// positions          // colors           // texture coords
		1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		1.0f, -0.70f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		0.75f, -0.70f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		0.75f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left  
	};
	unsigned int indicesPipes[] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};

	unsigned int VBOPipes, VAOPipes, EBOPipes;
	glGenVertexArrays(1, &VAOPipes);
	glGenBuffers(1, &VBOPipes);
	glGenBuffers(1, &EBOPipes);

	glBindVertexArray(VAOPipes);

	glBindBuffer(GL_ARRAY_BUFFER, VBOPipes);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPipes), verticesPipes, GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOPipes);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesPipes), indicesPipes, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Using soil to load a bird with ease...
	GLuint textureBird = SOIL_load_OGL_texture
	(
		"bird.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	GLuint textureFloor = SOIL_load_OGL_texture
	(
		"floor.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	GLuint texturePipes = SOIL_load_OGL_texture
	(
		"pipes.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);

		//render
		glClearColor(0.0f, 0.7f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ourShader.Activate();
		displayFunc(textureBird, textureFloor, texturePipes, VAO, VAOFloor, VAOPipes);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


