// -----------------------------
// Made by Tomáš Sobota, SOB0111
// -----------------------------

#include "Application.h"
#include "Inputs/Input.h"

int main(void) {
	Application* application = Application::getInstance();
	application->init();
	application->createShaders();
	application->createModels();
	
	application->run();
	
	delete application;
	delete Input::getInstance();
	exit(EXIT_SUCCESS);
}
