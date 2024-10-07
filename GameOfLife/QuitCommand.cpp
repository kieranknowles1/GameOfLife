#include "QuitCommand.h"

#include "Controller.h"

namespace GameOfLife {

	void QuitCommand::execute(Controller* controller)
	{
		controller->requestQuit();
	}
}