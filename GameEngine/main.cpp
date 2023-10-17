// -----------------------------
// Made by Tomáš Sobota, SOB0111
// -----------------------------

#include "Application.h"
#include "Inputs/Input.h"

int main(void) {
	shared_ptr<Application> application = Application::getInstance();
	application->init();
	application->createShaders();
	application->createModels();
	
	application->run();
	
	exit(EXIT_SUCCESS);
}
