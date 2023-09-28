// -----------------------------
// Made by Tomáš Sobota, SOB0111
// -----------------------------

#include "Aplication.h"
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

#include "Inputs/Listeners/TestKeyListener.h"

// Callbacks
static void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

static void window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n");
}

static void window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n");
}

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

//GLM test

// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);

float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

int main(void) {
	Aplication* ap = Aplication::getInstance();
	ap->init();
	ap->createShaders();
	ap->createModels();
	ap->run();

	ap->getInput()->addListenerOnKey(new TestKeyListener());
	
	// Sets the key callback
	glfwSetWindowFocusCallback(ap->getWindow(), window_focus_callback);
	glfwSetWindowIconifyCallback(ap->getWindow(), window_iconify_callback);
	glfwSetWindowSizeCallback(ap->getWindow(), window_size_callback);
	
	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
	//Vertex Array Object (VAO)
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	
	while (!glfwWindowShouldClose(ap->getWindow())) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(ap->getWindow());
	}
	glfwDestroyWindow(ap->getWindow());
	glfwTerminate();
	exit(EXIT_SUCCESS);
}