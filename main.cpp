#include<iostream>
#include<glad/glad.h>
#include<KHR/khrplatform.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>
#include<glut/glut.h>
#include"shaderClass.h"
#include"bird.h"
#include"pipes.h"
#include"ground.h"
#include<ctime>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, bird* b) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		b->reinit(-b->gravity);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		b->reinit((b->gravity));
	}

}
void displayFunc(bird b, ground g, pipes p, pipes p2) {
	// bind bird Texture
	glBindTexture(GL_TEXTURE_2D, b.texture);

	// render container
	glBindVertexArray(b.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
	// bind floor Texture
	glBindTexture(GL_TEXTURE_2D, g.texture);

	// render container
	glBindVertexArray(g.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	// bind floor Texture
	glBindTexture(GL_TEXTURE_2D, p.texture);

	// render container
	glBindVertexArray(p.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// bind floor Texture
	glBindTexture(GL_TEXTURE_2D, p2.texture);

	// render container
	glBindVertexArray(p2.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void moveObjects(bird* b, pipes* p, pipes* p2, float gravity) {
	p->reinit();
	p2->reinit();
}
void checkCollision(bird* b, pipes* p, pipes* p2) {
	/*if (b->vertices[0] == p->vertices[15] || b->vertices[0] == p2->vertices[15]) {
		p->speed = 0.0f;
		p2->speed = 0.0f;
	}*/
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
	Shader birdShader("bird.vert", "bird.frag");

	//Create our objects for the three main sprites.
	bird* b = new bird;
	ground g;
	pipes* p = new pipes(0);
	pipes* p2 = new pipes(1.125);

	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window, b);

		//render
		glClearColor(0.0f, 0.7f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ourShader.Activate();

		
		moveObjects(b, p,p2, b->gravity);
		checkCollision(b, p, p2);
		displayFunc(*b, g, *p, *p2);
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}

	b->del();
	g.del();
	p->del();
	p2->del();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


