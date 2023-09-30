// -----------------------------
// Made by Tomáš Sobota, SOB0111
// -----------------------------

#include "Application.h"
#include "Inputs/Listeners/TestKeyListener.h"

int main(void) {
	Application* application = Application::getInstance();
	application->init();
	application->createShaders();
	application->createModels();
	
	Input::getInstance()->addListenerOnKey(new TestKeyListener());
	
	application->run();
	
	delete application;
	delete Input::getInstance();
	exit(EXIT_SUCCESS);
}
