#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>
#include"shaderClass.h"
#include"bird.h"
#include"pipes.h"
#include"ground.h"

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
	bird b;
	pipes p;
	ground f;
	

	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);

		//render
		glClearColor(0.0f, 0.7f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ourShader.Activate();
		displayFunc(b.texture, f.texture, p.texture, b.VAO, f.VAO, p.VAO);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


