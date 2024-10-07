#include "HelpCommand.h"

#include <iostream>

#include "Controller.h"

namespace GameOfLife {
	// TODO: Implement
	void HelpCommand::execute(Controller* context)
	{
		std::cout << "This is a help message\n";

		context->requestQuit();
	}
}