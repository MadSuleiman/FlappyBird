#include<iostream>
#include"Libraries/include/glad/glad.h"
#include"Libraries/include/KHR/khrplatform.h"
#include"Libraries/include/GLFW/glfw3.h"
#include"shaderClass.h"
#include"./objects/bird.h"
#include"./objects/pipes.h"
#include"./objects/ground.h"
#include"./objects/generic.h"
#include<ctime>


bool gameStart = false;
bool gameEnd = false;
void jump(bird* b);

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, bird* b) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (!gameStart) {
			glfwSetTime(0);
			gameStart = true;
		}
		jump(b);
	}
	if (gameStart) {
		// if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		// 	b->reinit(-b->gravity);
		// }
		// if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		// 	b->reinit((b->gravity));
		// }
	}

}
void displayStart(generic logo, generic btn) {
	// bind bird Texture
	glBindTexture(GL_TEXTURE_2D, logo.texture);

	// render container
	glBindVertexArray(logo.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// bind floor Texture
	glBindTexture(GL_TEXTURE_2D, btn.texture);

	// render container
	glBindVertexArray(btn.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void displayEnd(generic end) {
	// bind bird Texture
	glBindTexture(GL_TEXTURE_2D, end.texture);

	// render container
	glBindVertexArray(end.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void displayFunc(bird b, ground g, pipes p, pipes p2, generic clouds) {
	// bind bird Texture
	glBindTexture(GL_TEXTURE_2D, clouds.texture);

	// render container
	glBindVertexArray(clouds.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// bind bird Texture
	glBindTexture(GL_TEXTURE_2D, b.texture);

	// render container
	glBindVertexArray(b.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
	// bind pipe Texture
	glBindTexture(GL_TEXTURE_2D, p.texture);

	// render container
	glBindVertexArray(p.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// bind pipe Texture
	glBindTexture(GL_TEXTURE_2D, p2.texture);

	// render container
	glBindVertexArray(p2.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// bind floor Texture
	glBindTexture(GL_TEXTURE_2D, g.texture);

	// render container
	glBindVertexArray(g.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}
//Function used to implement a 'jump' for the bird. alters the bird's gravity
void jump(bird* b){
	glfwSetTime(0);
	b->gravity = -0.01f;	
}
//function serves to implement pipe speed and gravity. Can be easily changed for a differnet gaming experience.
void addSpeed(pipes* p, pipes* p2, bird* b) {
	// p->speed = 0.0002f + float(glfwGetTime()/10000);
	// p2->speed = 0.0002f + float(glfwGetTime()/10000);
	p->speed = 0.005f;
	p2->speed = 0.005f;
	b->gravity += 0.0005f;
}
//function to change our booleans
void endGame() {
	gameStart = false;
	gameEnd = true;
}
//changes our vertices with updated values, so that when drawn, the next frame shows the updated graphic
void moveObjects(pipes* p, pipes* p2, bird* b) {
	p->reinit();
	p2->reinit();
	b->reinit(b->gravity);
}
//Our collision checker.
void checkCollision(bird* b, pipes* p, pipes* p2, ground g) {
	//checks if the right corners of the bird are the the same as the pipes
	if (b->vertices[0] >= p->vertices[15] && b->vertices[0] <= p->vertices[0]) {
		//if it is, check if the correct height is met.
		if (!(b->vertices[1] <= p->vertices[16] - 0.98f && b->vertices[1] >= p->vertices[16] - 1.45f)) {
			p->speed = 0.0f; //This is where you would add a gameover screen
			p2->speed = 0.0f;
			endGame();
		}
	}
	if (b->vertices[0] >= p2->vertices[15] && b->vertices[0] <= p2->vertices[0]) {
		//if it is, check if the correct height is met.
		if (!(b->vertices[1] <= p2->vertices[16] - 0.98f && b->vertices[1] >= p2->vertices[16] - 1.45f))  {
			p->speed = 0.0f; //This is where you would add a gameover screen
			p2->speed = 0.0f;
			endGame();
		}
	}
	if (b->vertices[6] <= -0.69f) {
		p->speed = 0.0f; //This is where you would add a gameover screen
		p2->speed = 0.0f;
		endGame();
	}

}

int main() {
	//Initialize glfw, our window opening library.
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

	//Create an object for our logo and start button
	float v1[20] = {
		// positions          // texture coords
		0.4f,  0.70f, 0.0f,      1.0f, 1.0f,   // top right
		0.4f, 0.40f, 0.0f,      1.0f, 0.0f,   // bottom right
		-0.40f, 0.40f, 0.0f,     0.0f, 0.0f,   // bottom left
		-0.40f,  0.70f, 0.0f,     0.0f, 1.0f    // top left 
	};
	generic logo("./textures/logo.png", v1);
	float v2[20] = {
		// positions          // texture coords
		0.2f,  -0.30f, 0.0f,      1.0f, 1.0f,   // top right
		0.2f, -0.60f, 0.0f,      1.0f, 0.0f,   // bottom right
		-0.20f, -0.60f, 0.0f,     0.0f, 0.0f,   // bottom left
		-0.20f,  -0.30f, 0.0f,     0.0f, 1.0f    // top left 
	};
	generic btn("./textures/playbtn.png", v2);
	float v3[20] = {
		// positions          // texture coords
		0.25f,  1.0f, 0.0f,      1.0f, 1.0f,   // top right
		0.25f, 0.5f, 0.0f,      1.0f, 0.0f,   // bottom right
		-0.25f, 0.5f, 0.0f,     0.0f, 0.0f,   // bottom left
		-0.25f,  1.0f, 0.0f,     0.0f, 1.0f    // top left 
	};
	generic end("./textures/died.jpg", v3);
	float v4[20] = {
		// positions          // texture coords
		1.0f,  1.0f, 0.0f,      1.0f, 1.0f,   // top right
		1.0f, 0.6f, 0.0f,      1.0f, 0.0f,   // bottom right
		-1.0f, 0.6f, 0.0f,     0.0f, 0.0f,   // bottom left
		-1.0f,  1.0f, 0.0f,     0.0f, 1.0f    // top left 
	};
	generic clouds("./textures/clouds.gif", v4);


	//Create our objects for the three main sprites.
	bird* b = new bird;
	ground g;
	pipes* p = new pipes(-0.125f);
	pipes* p2 = new pipes(1.0f);
	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window, b);

		//render
		glClearColor(0.0f, 0.7f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ourShader.Activate();
		
		//scene selection
		if(!gameStart && !gameEnd)
			displayStart(logo, btn);
		if (!gameEnd) {
			displayFunc(*b, g, *p, *p2, clouds);
			if (gameStart) {
				moveObjects(p, p2, b);
				checkCollision(b, p, p2, g);
				addSpeed(p, p2, b);
			}
		}
		else {
			displayEnd(end);
		}
		
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


