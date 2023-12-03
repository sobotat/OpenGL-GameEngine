// -----------------------------
// Made by Tomáš Sobota, SOB0111
// -----------------------------

#include "Application.h"

int main(void) {
	shared_ptr<Application> application = Application::getInstance();
	application->init();	
	application->run();
	
	exit(EXIT_SUCCESS);
}
