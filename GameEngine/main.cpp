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


int main(void) {
	Aplication* aplication = Aplication::getInstance();
	aplication->init();
	aplication->createShaders();
	aplication->createModels();

	// Sets the key callback
	glfwSetWindowFocusCallback(aplication->getWindow(), window_focus_callback);
	glfwSetWindowIconifyCallback(aplication->getWindow(), window_iconify_callback);
	glfwSetWindowSizeCallback(aplication->getWindow(), window_size_callback);
	
	aplication->getInput()->addListenerOnKey(new TestKeyListener());
	
	aplication->run();
}