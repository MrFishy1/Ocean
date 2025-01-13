#include "Sandbox.hpp"

#include "Ocean/Core/Application.hpp"

#include "Ocean/Core/Primitives/Macros.hpp"

Ocean::Application* Ocean::CreateApplication() {
	Ocean::ApplicationConfig config("Ocean Sandbox", 1200, 800);

	return new Sandbox(config);
}



Sandbox::Sandbox(const Ocean::ApplicationConfig& config) : Ocean::Application(config) {
	oprint(CONSOLE_TEXT_CYAN("Constructing Sandbox Application!\n"));
}

Sandbox::~Sandbox() {
	oprint(CONSOLE_TEXT_CYAN("Deconstructing Sandbox Application!\n"));	
}
